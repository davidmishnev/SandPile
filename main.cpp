#include "src/tsv.h"
#include "src/bmp.h"
#include "src/ParseArguments.h"
#include "src/sandpile.h"

int main(int arg_count, char** argv) {
    ArgsParser parse_args(arg_count, argv);
    parse_args.Parse();
    Options user_arguments = parse_args.GetUserArgs();
    std::cout << "input_filepath=" << user_arguments.input_filepath << "\n";
    std::cout << "output_dir=" << user_arguments.output_dir << "\n";
    std::cout << "max_iter=" << user_arguments.max_iter << "\n";
    std::cout << "frequency=" << user_arguments.frequency << "\n";
    std::cout << "print_console=" << user_arguments.print_console << "\n\n";
    TsvReader input_tsv = TsvReader(user_arguments.input_filepath);
    SandyMatrix* sandy_matrix = input_tsv.Parse();
    bool change = true;
    BMPWriter bmp_writer(user_arguments);
    while (sandy_matrix -> step < user_arguments.max_iter && change) {
        if (sandy_matrix -> step % 10 == 0) {
            printf("Step: %d\r", sandy_matrix -> step);
        }
        if (user_arguments.frequency != 0 && sandy_matrix -> step % user_arguments.frequency == 0) {
            bmp_writer.Write(sandy_matrix);
            if (user_arguments.print_console) {
                system("clear");
                sandy_matrix -> printMatrix(" ");
            }
        }
        change = sandy_matrix->calcStep();
    }
    printf("Step: %d\r\n", sandy_matrix -> step);
    if (user_arguments.print_console) {
        system("clear");
        sandy_matrix -> printMatrix(" ");
    }
    bmp_writer.Write(sandy_matrix);
    delete &bmp_writer;
    delete sandy_matrix;
}