/** A TOOL CREATED TO EMBED OPENGL SHADERS DIRECTLY INTO A HPP - CPP FILE
 *  TO MAKE IT SIMPLER TO WORK WITH.
 *
 *  YOU SHOULD BE ABLE TO COMPILE THIS BEFORE AND RUN IT WITH YOUR BUILD SYSTEM
 *  BEFORE COMPILING THE ACTUAL APPLICATION SO THAT IT INCLUDES THE SHADER CODE
 */

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::filesystem;

// Define however many extensions you'd like for it to recursively search for!
const string shader_extensions[] = {".vert", ".frag"};
const string prefix              = "SHADER_";

struct FileContent {
    string filename;
    string content;
    FileContent(string filename, string content) : filename(filename), content(content) {}
};

string convert_filename(string filename) {
    replace(filename.begin(), filename.end(), '.', '_');
    return filename;
}

void trimLines(string* input) {
    size_t pos = 0;

    while (1) {
        size_t start = input->find("\n", pos);
        size_t end   = 0;

        if (start == string::npos) break;

        const char* ptr = input->c_str() + start + 1;
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
            end++;
        };

        input->erase(start + 1, end);
        pos = start + 1;
    }
}

string removeEmptyLines(string& input) {
    string output;
    bool previousLine = false;

    for (char c : input) {
        if (c == '\n') {
            if (!previousLine) output += c;

            previousLine = true;
        }

        else {
            output += c;
            previousLine = false;
        }
    }

    if (output.back() == '\n') output.pop_back();

    return output;
}

void removeComments(string* input) {
    size_t pos = 0;

    while (1) {
        size_t start = input->find("//", pos);
        size_t end   = input->find('\n', start);

        if (start == string::npos || end == string::npos) break;

        input->erase(start, end - start);
        pos = end - start;
    }
}

void stringify(string* content) {
    size_t it = 0;
    while (1) {
        size_t pos = content->find('\n', it);
        if (pos >= content->size()) break;

        content->insert(pos + 1, "\"");
        content->insert(pos, "\\n\"");
        it = pos + 4;
    }
}

string convert_content(string content) {
    removeComments(&content);
    trimLines(&content);
    content = removeEmptyLines(content);
    stringify(&content);

    return content;
}

string create_header_template(vector<FileContent>& file) {
    ostringstream header;
    header << "#ifndef EMBED_SHADER_FILE_GUARD_\n";
    header << "#define EMBED_SHADER_FILE_GUARD_\n\n";

    for (auto& file : file) {
        header << "extern const char* " << prefix << convert_filename(file.filename) << ";\n";
    }

    header << "\n#endif // EMBED_SHADER_FILE_GUARD_\n";
    return header.str();
}

string create_source_template(vector<FileContent>& files) {
    ostringstream source;

    source << "#include \"shaders.hpp\"\n\n";

    for (auto& file : files) {
        source << "const char* " << prefix << convert_filename(file.filename) << " = ";
        source << "\"" << convert_content(file.content) << "\";\n\n";
    }

    return source.str();
}

vector<FileContent> get_files_recursively(string directory) {
    vector<FileContent> files;

    for (recursive_directory_iterator i(directory), end; i != end; i++) {
        if (!is_directory(i->path())) {
            string ext = i->path().extension();

            for (auto& e : shader_extensions) {
                if (ext.compare(e) == 0) {
                    i->path().extension();
                    string filename = i->path().filename();
                    ifstream input(i->path());
                    ostringstream contentStream;
                    contentStream << input.rdbuf();

                    FileContent file = FileContent(filename, contentStream.str());
                    files.push_back(file);
                    break;
                }
            }
        };
    }

    return files;
}

bool shaders_has_updated(string path, string new_shader) {
    ifstream old_file(path);

    if (old_file.is_open()) {
        ostringstream stream;
        stream << old_file.rdbuf();
        string old_content = stream.str();

        return old_content.compare(new_shader);
    }

    return true;
}

void try_save_shader(string path, string content) {
    if (shaders_has_updated(path, content)) {
        ofstream source_file(path);
        source_file << content;
        source_file.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Missing Arguments, Require: (File Input, File Output)\n";
        return 1;
    }

    string input_dir  = argv[1];
    string output_dir = argv[2];

    // recursively checks the input directories for files
    // might be worth to look for specific extension in the future
    // to avoid reading the wrong files.
    vector<FileContent> files = get_files_recursively(input_dir);

    // Create the correct templates for the .cpp and .hpp files
    string new_header = create_header_template(files);
    string new_source = create_source_template(files);

    string source_path = output_dir + "/shaders.cpp";
    string header_path = output_dir + "/shaders.hpp";

    // check if the file has updated before overwriting it
    try_save_shader(source_path, new_source);
    try_save_shader(header_path, new_header);

    return 0;
}
