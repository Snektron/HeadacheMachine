#include <iostream>
#include <fstream>
#include <string>

struct Context {
    std::istream& in;
    std::ostream& out;
    std::string& type;
    bool standalone;
};

void expr(std::istream& in, std::ostream& out);

std::string readline(std::istream& in) {
    std::string str;
    
    while (in.peek() != '\n' && !in.eof()) {
        str.append(1, in.get());
    }

    in.get();
    return str;
}

void list(std::istream& in, std::ostream& out) {
    if (in.peek() != '(') {
        std::cerr << "Expected '(', found '" << in.get() << '\'' << std::endl;
        exit(0); 
    }

    in.get();
    out << "List<";

    bool first(true);

    while (!in.eof()) {
        if (in.peek() == ')') {
            out << ">";
            in.get();
            return;
        }

        if (first)
            first = false;
        else
            out << ", ";

        expr(in, out);
    }

    std::cerr << "Unmatched ')'" << std::endl;
    exit(0);
}

void integer(std::istream& in, std::ostream& out) {
    int value = 0;
    while (!in.eof() && isdigit(in.peek())) {
        value *= 10;
        value += in.get() - '0';
    }

    out << "Int<" << value << ">";
}

void symbol(std::istream& in, std::ostream& out) {
    std::string sym;

    while (!in.eof()) {
        switch (in.peek()) {
        case 'a' ... 'z':   
        case 'A' ... 'Z':
        case '-':
        case '+':
        case '*':
        case '/':
        case '?':
            sym.append(1, in.get());
            continue;
        default:
            goto end;
        }
    }
    end:

    out << "Sym<'";
    bool first(true);

    for (char c : sym) {
        if (first)
            first = false;
        else
            out << "', '";
        out << c;
    }

    out << "'>";
}

void expr(std::istream& in, std::ostream& out) {
    while (!in.eof()) {
        switch (in.peek()) {
        case ';':
            readline(in);
            continue;
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            in.get();
            continue;
        case '(':
            list(in, out);
            return;
        case '0' ... '9':
            integer(in, out);
            return;
        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '-':
        case '+':
        case '*':
        case '/':
        case '?':
            symbol(in, out);
            return;
        case -1:
            return;
        default:
            std::cerr << "Unknown token " << (char) in.peek() << std::endl;
            exit(0);
        }
    }
}

void parse(std::istream& in, std::ostream& out) {
    out << "List<";

    bool first(true);

    while(!in.eof() && in.peek() != -1) {
        if (first)
            first = false;
        else
            out << ", ";

        expr(in, out);
    }

    out << ">";
}

void includes(Context& ctx) {
    ctx.out <<
        "#include \"atom/bool.h\"\n"
        "#include \"atom/closure.h\"\n"
        "#include \"atom/int.h\"\n"
        "#include \"atom/list.h\"\n"
        "#include \"atom/sym.h\"\n";

    if (ctx.standalone) {
        ctx.out <<
            "#include \"trait/eval.h\"\n"
            "#include \"trait/evalfunc.h\"\n"
            "#include \"trait/tostr.h\"\n"
            "#include \"env.h\"\n"
            "#include <iostream>\n";
    }

    ctx.out << std::endl;
}

void standalone(Context& ctx) {
    ctx.out <<
        "\n"
        "int main() {\n"
        "\tstd::cout << ToStr<EvalFunc<Primitives, " << ctx.type << ">::eval>::str::value << std::endl;\n"
        "\treturn 0;\n"
        "}\n";
}

void generate(Context& ctx) {
    includes(ctx);

    ctx.out << "using " << ctx.type << " = ";
    parse(ctx.in, ctx.out);
    ctx.out << ";\n";

    if (ctx.standalone)
        standalone(ctx);
}

int main(int argc, char *argv[]) {
    std::ifstream infile;
    std::ofstream outfile;
    std::string type("program");
    bool standalone(false);

    for (int i = 1; i < argc; i++) {
        std::string param(argv[i]);
        if (param == "-i" || param == "--input") {
            i++;
            if (i < argc) {
                infile.open(argv[i]);
                if (!infile) {
                    std::cerr << "Failed to open input " << argv[i] << std::endl;
                    return 0;
                }
            } else
                goto value_required;
        } else if (param == "-o" || param == "--output") {
            i++;
            if (i < argc) {
                outfile.open(argv[i]);
                if (!outfile) {
                    std::cerr << "Failed to open output " << argv[i] << std::endl;
                    return 0;
                }
            } else
                goto value_required;
        } else if (param == "-t" || param == "--type") {
            i++;
            if (i < argc)
                type = argv[i];
            else 
                goto value_required;
        } else if (param == "-s" || param == "--standalone")
            standalone = true;
        else if (param == "-h" || param == "--help") {
            std::cerr << 
                "Usage: " << argv[0] << " [options...]\n"
                "\n"
                "Options:\n"
                "-i, --input\t set input file (stdin by default)\n"
                "-o, --output\t set output file (stdout by default)\n"
                "-t, --type\t set program typename ('program' by default)\n"
                "-s, --standalone\t generate standalone source (off by default)\n"
                "-h, --help\t show this message" << std::endl;
            return 0;
        } else {
            std::cerr << "Unknown parameter '" << argv[i] << "'" << std::endl;
            return 0;
        }
    }

    {
        Context ctx = {
            infile.is_open() ? infile : std::cin,
            outfile.is_open() ? outfile : std::cout,
            type,
            standalone
        };
        generate(ctx);
    }

    return 0;

value_required:
    std::cerr << "Value required after " << argv[argc - 1] << std::endl;
    return 0;
}