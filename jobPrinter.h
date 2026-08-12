#ifndef HOA5SP_JOBPRINTER_H
#define HOA5SP_JOBPRINTER_H
#include <iostream>
#include <string>

class Job {
private:
    int job_id;
    std::string username;
    int numpages;

public:
    Job(int id = 0, std::string user = "", int pages = 0);

    int getId() const;
    std::string getUser() const;
    int getPages() const;

    void print() const;
};

Job::Job(int id, std::string user, int pages)
    : job_id(id),
      username(user),
      numpages(pages) {
}

int Job::getId() const {
    return job_id;
}

std::string Job::getUser() const {
    return username;
}

int Job::getPages() const {
    return numpages;
}

void Job::print() const {
    std::cout << "Job #" << job_id << " (" << username << ", " << numpages << " pages)";
}

#endif // HOA5SP_JOBPRINTER_H