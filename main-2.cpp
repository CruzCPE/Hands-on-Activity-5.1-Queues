#include <iostream>
#include <string>
#include "jobPrinter.h"
#include "printer.h"

int main() {

    Printer printer(10);
    int numPrint = 0;

    std::cout << "How many jobs do you want to print? ";
    std::cin >> numPrint;

    int next_id = 1;

    // Initial jobs
    for (int i = 0; i < numPrint; i++) {

        std::string name;
        int pages;

        std::cout << "\nEnter your name: ";
        std::cin >> name;

        std::cout << "Enter the number of pages: ";
        std::cin >> pages;

        printer.aJob(Job(next_id, name, pages));
        next_id++;
    }

    int incomingPrint = 0;

    std::cout << "\nHow many more jobs will come in while the printer runs? ";
    std::cin >> incomingPrint;

    // Incoming jobs
    for (int round = 0; round < incomingPrint; round++) {

        std::cout << "\n New Incoming Request " << std::endl;

        std::string name;
        int pages;

        std::cout << "Enter your name: ";
        std::cin >> name;

        std::cout << "Enter number of pages: ";
        std::cin >> pages;

        printer.aJob(Job(next_id, name, pages));
        next_id++;

        // Process one job
        if (!printer.Empty()) {
            std::cout << "\nPrinter is processing a job" << std::endl;
            printer.pJob();
        }
    }

    // Process remaining jobs
    std::cout << "\n Printing Remaining Queue " << std::endl;

    while (!printer.Empty()) {
        printer.pJob();
    }

    std::cout << "\nNo more incoming jobs and the queue is empty."
              << std::endl;

    std::cout << "Shutting down." << std::endl;

    return 0;
}