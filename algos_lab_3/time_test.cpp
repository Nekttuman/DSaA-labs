#include "mySorts.h"
#include "time_test.h"

void write_working_time_to_file(sortType st, std::fstream &file, std::vector<int> random_data,
                                std::vector<int> ascending_sorted_data, std::vector<int> descending_sorted_data) {
    auto start = std::chrono::high_resolution_clock::now();

    void (*sort_func)(std::vector<int>::iterator, std::vector<int>::iterator);

    if (st == sortType::bubble)
        sort_func = mySorts::bubbleSort;
    else if (st == sortType::shell)
        sort_func = mySorts::shellSort;
    else if (st == sortType::quick)
        sort_func = mySorts::quickSort;
    else if (st == sortType::insertion)
        sort_func = mySorts::insertionSort;
    else if (st == sortType::merge)
        sort_func = mySorts::mergeSort;
    else if (st == sortType::selection)
        sort_func = mySorts::selectionSort;
    else if (st == sortType::std_sort)
        sort_func = std::sort;
    else throw;

    sort_func(std::begin(random_data), std::end(random_data));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    file << duration.count() << ":";

    //asc test
    start = std::chrono::high_resolution_clock::now();

    sort_func(std::begin(ascending_sorted_data), std::end(ascending_sorted_data));

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    file << duration.count() << ":";

    //dsc test
    start = std::chrono::high_resolution_clock::now();

    sort_func(std::begin(descending_sorted_data), std::end(descending_sorted_data));

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    file << duration.count() << " ";

}

void algorithms_time_test() {
    std::fstream bubble_file("../tests_time/bubble_sort.txt", std::ios_base::out),
            insertion_file("../tests_time/insertion_sort.txt", std::ios_base::out),
            merge_file("../tests_time/merge_sort.txt", std::ios_base::out),
            quick_file("../tests_time/quick_sort.txt", std::ios_base::out),
            selection_file("../tests_time/selection_sort.txt", std::ios_base::out),
            shell_file("../tests_time/shell_sort.txt", std::ios_base::out),
            std_sort_file("../tests_time/std_sort.txt", std::ios_base::out);

    if (!bubble_file.is_open() || !insertion_file.is_open() || !merge_file.is_open() ||
        !quick_file.is_open() || !selection_file.is_open() || !shell_file.is_open() || !std_sort_file.is_open()) {
        std::cout << "ERR: one if files in algorith_time_test not opened\n";
        return;
    }

    std::vector<int> random_data;
    std::vector<unsigned> data_lens = {2, 10, 20, 40, 60, 80, 100, 1000, 10000, 20000, 30000};//, 40000, 50000, 70000,
                                       //100000};

    for (auto data_len: data_lens) {
        // generate random random_data[data_len]
        for (unsigned j = 0; j < data_len; ++j) {
            std::random_device rd;
            std::mt19937 rng(rd());
            int max_val = int(std::pow(2, sizeof(int) * 4));
            std::uniform_int_distribution<int> uni(-max_val, max_val);

            random_data.push_back(uni(rng));
        }
        std::vector<int> ascending_sorted_data, descending_sorted_data;

        for (int i = 0; i < data_len; ++i) {
            ascending_sorted_data.push_back(i);
            descending_sorted_data.push_back(int(data_len) - i);
        }


        std::thread bubble(write_working_time_to_file, sortType::bubble, std::ref(bubble_file), random_data,
                           ascending_sorted_data, descending_sorted_data),
                selection(write_working_time_to_file, sortType::selection, std::ref(selection_file), random_data,
                          ascending_sorted_data, descending_sorted_data),
                merge(write_working_time_to_file, sortType::merge, std::ref(merge_file), random_data, ascending_sorted_data,
                      descending_sorted_data),
                insertion(write_working_time_to_file, sortType::insertion, std::ref(insertion_file), random_data,
                          ascending_sorted_data, descending_sorted_data),
                quick(write_working_time_to_file, sortType::quick, std::ref(quick_file), random_data, ascending_sorted_data,
                      descending_sorted_data),
                shell(write_working_time_to_file, sortType::shell, std::ref(shell_file), random_data, ascending_sorted_data,
                      descending_sorted_data),
                std_sort(write_working_time_to_file, sortType::std_sort, std::ref(std_sort_file), random_data,
                         ascending_sorted_data, descending_sorted_data);


        if (selection.joinable()) selection.join();
        if (bubble.joinable()) bubble.join();
        if (merge.joinable()) merge.join();
        if (insertion.joinable()) insertion.join();
        if (quick.joinable()) quick.join();
        if (shell.joinable()) shell.join();
        if (std_sort.joinable()) std_sort.join();

        random_data.clear();
        ascending_sorted_data.clear();
        descending_sorted_data.clear();
        std::cout << data_len << " \n";
    }
    bubble_file.close();
    shell_file.close();
    selection_file.close();
    insertion_file.close();
    merge_file.close();
    quick_file.close();
    std_sort_file.close();
}

// it could be an alternative for write_working_time_to_file func, but I can't get function return value in
// std::thread and I can't put another function (sortFunc) as a param for std::thread
long long get_working_time(void (*sortFunc)(std::vector<int>::iterator, std::vector<int>::iterator),
                           std::vector<int> data) {
    auto start = std::chrono::high_resolution_clock::now();

    sortFunc(std::begin(data), std::end(data));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();
}