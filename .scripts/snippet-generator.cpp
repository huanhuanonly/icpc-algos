#include <iostream>
#include <fstream>
#include <filesystem>

#include <vector>
#include <list>

#include <ranges>
#include <algorithm>

#define INSTRUCTION_NAME "snippet-generator"

inline namespace huanhuanonly
{
class snippet_generator
{
public:

    enum target_format
    {
        vscode_json
    };

    struct item
    {
        std::string description;
        std::string tab_trigger;
        std::string snippet;
    };

    void
    append(const std::vector<std::string>& __module, const item& __item)
    {
        item item = __item;
        merge_module_to_snippet(__module, item.snippet);

        m_data.emplace_back(std::move(item));
    }

    [[nodiscard]] std::size_t
    count() const
    {
        return m_data.size();
    }

    void
    write(std::ostream& __os, target_format __format)
    {
        switch (__format)
        {
        case vscode_json:
            write_vscode_json(__os);
        }
    }

protected:

    virtual void
    merge_module_to_snippet(const std::vector<std::string>& __module, std::string& __snippet)
    { }

    static void
    write_spaces(std::ostream& __os, int __n)
    {
        for (; __n--; __os.put(' '));
    }

    void
    write_vscode_json(std::ostream& __os)
    {
        __os << "{\n";

        constexpr int indent = 2;
        constexpr int indent_step = 2;

        bool first_item = true;

        for (const auto& [description, tab_trigger, snippet] : m_data)
        {
            if (not first_item)
            {
                __os << ",\n\n";
            }

            first_item = false;

            write_spaces(__os, indent);
            __os << "\"" << json_escape(description) << "\": {\n";

            write_spaces(__os, indent + indent_step);
            __os << "\"prefix\": \"" << json_escape(tab_trigger) << "\",\n";

            write_spaces(__os, indent + indent_step);
            __os << "\"body\": [\n";

            auto emit_line = [&, first_line = true](std::string_view __line) mutable -> void
            {
                if (not __line.empty() and __line.back() == '\r')
                {
                    __line.remove_suffix(1);
                }

                if (not first_line)
                {
                    __os << ",\n";
                }

                first_line = false;

                write_spaces(__os, indent + indent_step * 2);
                __os << "\"" << json_escape(__line) << "\"";
            };

            for (std::size_t start = 0; start <= snippet.size(); )
            {
                const std::size_t pos = snippet.find('\n', start);

                if (pos == std::string_view::npos)
                {
                    emit_line(std::string_view(snippet.begin() + start, snippet.end()));
                    break;
                }
                else
                {
                    emit_line(std::string_view(snippet.begin() + start, snippet.begin() + pos));
                    start = pos + 1;
                }
            }

            __os << '\n';
            write_spaces(__os, indent + indent_step);
            __os << "],\n";

            write_spaces(__os, indent + indent_step);
            __os << "\"description\": \"" << json_escape(description) << "\"\n";

            write_spaces(__os, indent);
            __os << "}";
        }

        __os << "\n}\n";
    }

    [[nodiscard]] static std::string
    json_escape(std::string_view __s)
    {
        std::string out;
        out.reserve(__s.size() + 8);

        static auto hex = [](unsigned char __v) -> char
        {
            return "0123456789abcdef"[__v & 0xF];
        };

        for (const unsigned char c : __s)
        {
            switch (c)
            {
            case '\"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\b': out += "\\b";  break;
            case '\f': out += "\\f";  break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;

            default:
            
                if (c < 0x20)
                {
                    out += "\\u00";
                    out += hex(c >> 4);
                    out += hex(c);
                }
                else
                {
                    out += c;
                }
            }
        }

        return out;
    }

private:

    std::list<item> m_data;
};
}

inline namespace huanhuanonly
{
class cpp_snippet_generator : public snippet_generator
{
protected:

    virtual void
    merge_module_to_snippet(const std::vector<std::string>& __module, std::string& __snippet) override
    {
        if (__module.empty())
        {
            return;
        }

        std::string s;
        std::string e = " // namespace ";
        
        constexpr int indent = 4;

        int i = 0;

        for (const std::string& name : __module)
        {
            s.append(indent * i, ' ');
            s.append("inline namespace ");
            s.append(name);
            s.append(" {\n");

            if (i)
            {
                e.append("::");
            }

            ++i;

            e.append(name);
        }

        s.pop_back();
        s.pop_back();
        s.pop_back();

        s.append("\n{\n");

        s.append(__snippet);

        s.append("\n");
        s.append(__module.size(), '}');
        s.append(e);

        __snippet = std::move(s);
    }
};
}

[[nodiscard]] static std::string
file_content(const std::filesystem::path& __path)
{
    std::ifstream ifs(__path, std::ios::binary);
    std::string   content(std::filesystem::file_size(__path), '\0');

    ifs.read(content.data(), content.size());
    return content;
}

[[nodiscard]] static std::string
extract_description(const std::string& __s)
{
    static auto is_not_space = [](unsigned char __c) -> bool
    {
        return not std::isspace(__c);
    };

    std::string result = __s;

    result.erase(std::ranges::find_if(result | std::views::reverse, is_not_space).base(), result.end());
    result.erase(result.begin(), std::ranges::find_if(result, is_not_space));

    return result;
}

[[nodiscard]] static std::string
extract_tab_trigger(const std::string& __s)
{
    static auto is_not_space = [](unsigned char __c) -> bool
    {
        return not std::isspace(__c);
    };
    
    std::string result;
    result.reserve(__s.size());
    
    const auto cnt = std::ranges::distance(
        std::ranges::find_if(__s | std::views::take(__s.find('[')) | std::views::reverse, is_not_space).base(),
        __s.end());

    bool found = false;

    for (const unsigned char c : __s | std::views::take(__s.size() - cnt))
    {
        if (not std::isspace(c))
        {
            found = true;
        }
        else if (not found)
        {
            continue;
        }

        if (std::isspace(c) or c == '_')
        {
            result.push_back('_');
        }
        else if (std::ispunct(c))
        {
            continue;
        }
        else
        {
            result.push_back(c);
        }
    }

    return result;
}

int
main(int argc, char* argv[])
{
    namespace fs = std::filesystem;

    if (fs::path(argv[0]).stem() != INSTRUCTION_NAME or argc != 3)
    {
        std::cerr << INSTRUCTION_NAME " <input_dir> <output_dir>\n";
        return 1;
    }

    try
    {
        fs::path input_dir = fs::path(argv[1]);
        fs::path output_dir = fs::path(argv[2]);

        if (not fs::exists(output_dir))
        {
            fs::create_directories(output_dir);
        }
        
        cpp_snippet_generator cpp_sg;

        std::vector<std::string> module_name{ "huanhuanonly" };

        for (fs::recursive_directory_iterator it(input_dir), end; it != end; ++it)
        {
            const auto& e = *it;
            const fs::path& epath = e.path();

            if (module_name.size() > it.depth() + 1)
            {
                module_name.resize(it.depth() + 1);
            }

            if (e.is_directory())
            {
                module_name.push_back(e.path().filename());
            }
            else if (e.is_regular_file())
            {
                if (epath.extension() == ".cpp" or epath.extension() == ".hpp")
                {
                    cpp_sg.append(module_name.back()[0] != '.' ? module_name : std::vector<std::string>{}, {
                        .description = extract_description(epath.stem()),
                        .tab_trigger = extract_tab_trigger(epath.stem()),
                        .snippet = file_content(epath)});
                }
                else
                {
                    std::clog << "In" INSTRUCTION_NAME ": Unsupported file extension " << epath.extension()
                        << " from file " << epath << '\n';
                }
            }
        }

        std::ofstream ofs(output_dir / "vscode.cpp.json", std::ios::binary);
        cpp_sg.write(ofs, snippet_generator::vscode_json);

        std::cout << "+ vscode.cpp.json@" << cpp_sg.count() << '\n';
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    catch (...)
    {
        return 3;
    }

    return 0;
}