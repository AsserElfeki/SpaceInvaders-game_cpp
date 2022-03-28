#include <iostream>
#include <filesystem>
//#include <chrono>
#include <map>

namespace fs = std::filesystem;

int main() {

    fs::path current = fs::current_path();
    std::cout << "path: " << current << "\n";
//std::cout << current.filename();

    std::cout << "### Task 3 ###\n";

    fs::path a("/Users/asser.elfeki/POLSL/CP 4/acbac343-gr12-repo/lab3/FileSystems/main.cpp");
    std::cout << "info about " << a << " : " << std::endl
              << "exists: " << fs::exists(a) << std::endl
              << "Root Name: " << a.root_name() << std::endl
              << "Root Path: " << a.root_path() << std::endl
              << "Relative Path: " << a.relative_path() << std::endl
              << "Parent Path: " << a.parent_path() << std::endl
              << "File name: " << a.filename() << std::endl
              << "Stem: " << a.stem() << std::endl
              << "Extension: " << a.extension() << std::endl;
    std::cout << "### Task 4 ###\n";
    std::cout << "info about " << current << " : " << std::endl
              << "exists: " << fs::exists(current) << std::endl
              << "Root Name: " << current.root_name() << std::endl
              << "Root Path: " << current.root_path() << std::endl
              << "Relative Path: " << current.relative_path() << std::endl
              << "Parent Path: " << current.parent_path() << std::endl
              << "File name: " << current.filename() << std::endl
              << "Stem: " << current.stem() << std::endl
              << "Extension: " << current.extension() << std::endl;


    std::cout << "### Task 5 ###\n";
    current /= "../main.cpp";
    std::cout << "info about " << current << " : " << std::endl
              << "exists: " << fs::exists(current) << std::endl
              << "Root Name: " << current.root_name() << std::endl
              << "Root Path: " << current.root_path() << std::endl
              << "Relative Path: " << current.relative_path() << std::endl
              << "Parent Path: " << current.parent_path() << std::endl
              << "File name: " << current.filename() << std::endl
              << "Stem: " << current.stem() << std::endl
              << "Extension: " << current.extension() << std::endl;


    std::cout << "### Task 6 ###\n";
    fs::path tasks = fs::current_path();
    tasks /= "../tasks/subdir1/shrek.txt";
//    auto cftime = std::chrono::system_clock::to_time_t(
//            std::chrono::file_clock::to_sys(fs::last_write_time(tasks)));
    std::cout << "info about " << tasks << " : " << std::endl
              << "exists: " << fs::exists(tasks) << std::endl
              << "Root Name: " << tasks.root_name() << std::endl
              << "Root Path: " << tasks.root_path() << std::endl
              << "Relative Path: " << tasks.relative_path() << std::endl
              << "Parent Path: " << tasks.parent_path() << std::endl
              << "File name: " << tasks.filename() << std::endl
              << "Stem: " << tasks.stem() << std::endl
              << "Extension: " << tasks.extension() << std::endl
              << "File Size: " << file_size(tasks) << std::endl;
    //<< "Last write Time: " << std::asctime(std::localtime(&cftime));

    std::cout << "### Task 7 ###\n";
    fs::copy(tasks, tasks.parent_path() /= "shrek2.txt", fs::copy_options::update_existing);

    std::cout << "### Task 8 ###\n";
    fs::path task_8 = fs::current_path();
    task_8 /= "../tasks/subdir2";
    std::cout << "info about " << task_8 << " : " << std::endl
              << "Is empty: " << is_empty(task_8) << std::endl
              << "Is Dierectory: " << is_directory(task_8) << std::endl;


    std::cout << "### Task 9 & 10 ###\n";

    fs::path task_9 = fs::current_path();
    task_9 /= "../filesystem";
    int i = 1;
    for (auto &dir: fs::recursive_directory_iterator{task_9}) {
        if (dir.path().extension() == ".rtf") {
            std::string name = "file" + std::to_string(i) + ".rtf";
            std::cout << dir.path().stem() << std::endl;
            fs::rename(dir.path(), dir.path().parent_path() /= name);
            i++;
        }
    }

    std::cout << "### Task 11 ###\n";
    fs::path task_11 = fs::current_path() /= "../filesystem";
    std::cout << task_11 << "\n";
    fs::path largest;
    int tmp{};
    for (auto &dir: fs::recursive_directory_iterator{task_11}) {
        if (!dir.is_directory() && dir.file_size() > tmp) {
            largest = dir.path();
            tmp = dir.file_size();
        }
    }
    std::cout << "the largest file is: " << largest.filename() << "its size is: " << file_size(largest) << std::endl;


    std::cout << "### Task 12 ###\n";
    fs::path task12 = fs::current_path() / "../filesystem";
    auto fileIterator = fs::recursive_directory_iterator(task12);
    std::map<int, std::string> map;
    for (auto &dir: fs::recursive_directory_iterator{task_11}) {
        if (!dir.is_directory() && dir.path().extension() == ".rtf")
            map.insert(std::pair<int, std::string>(dir.file_size(), dir.path().filename()));
        //std::cout << dir.path().filename() << std::endl;
    }

    for (auto &element: map) {
        std::cout << "File: " << element.second << " is of Size: " << element.first << " Bytes" << std::endl;
    }


    std::cout << "### Task 13 ###\n";
    fs::path from = fs::current_path() /= "../filesystem/subdir3";
    fs::path to_jpg = from / "ilovejpg";
    fs::path to_png = from / "ilovepng";

    for (auto& a : fs::directory_iterator{from}){
        if (a.path().extension() == ".jpg"){
            fs::rename (a.path(), to_jpg/a.path().filename());
        }
        if (a.path().extension() == ".png"){
        fs::rename (a.path(), to_png/a.path().filename());
        }
    }

    return 0;
}
/*


13.Familiarize with (filesystem/subdir3) directory, make it so that the files with "jpg" extension are moved to the (filesystem/
subdir3/ilovejpg) directory and files with "png" extension are moved to the (filesystem/subdir3/ilovepng) directory. */


