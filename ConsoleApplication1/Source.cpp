//#define CURL_STATICLIB
//#include "curl/curl.h"
//#include <iostream>
//#include <string>
//#include <thread>
//#include <fstream>
//#include <mutex>
//#include <vector>
//#ifdef _DEBUG
//#pragma comment(lib,"curl/libcurl_a_debug.lib")
//#else
//#pragma comment(lib,"curl/libcurl_a.lib")
//#endif
//
//#pragma comment(lib,"Normaliz.lib")
//#pragma comment(lib,"Ws2_32.lib")
//#pragma comment(lib,"Wldap32.lib")
//#pragma comment(lib,"Crypt32.lib")
//#pragma comment(lib,"Advapi32.lib")
//
//using namespace std;
//struct Range {
//    int start;
//    int end;
//};
//
//std::vector<std::pair<long long, long long>> get_download_ranges(long long content_length, int num_threads) {
//    std::vector<std::pair<long long, long long>> ranges;
//
//    long long part_size = 0;
//    long long remainder = 0;
//
//    // Determine the size of each part
//    if (content_length % num_threads == 0) {
//        part_size = content_length / num_threads;
//    }
//    else {
//        part_size = content_length / num_threads + 1;
//        remainder = content_length % num_threads;
//    }
//
//    // Calculate the range for each part
//    for (int i = 0; i < num_threads; i++) {
//        long long start = i * part_size;
//        long long end = (i + 1) * part_size - 1;
//
//        if (i == num_threads - 1) {
//            end += remainder;
//        }
//
//        ranges.push_back({ start, end });
//    }
//
//    return ranges;
//}
//
//
//int main() {
//    CURL* curl;
//    FILE* fp;
//    CURLcode res;
//    const char* url = "https://scontent.fsgn5-2.fna.fbcdn.net/v/t39.30808-6/340103743_473156954943582_2145573030445108477_n.jpg?_nc_cat=1&ccb=1-7&_nc_sid=5cd70e&_nc_ohc=fJpjVp9rxp4AX8yscd0&_nc_ht=scontent.fsgn5-2.fna&oh=00_AfD_wj5eWYSjOTr-jZksAUKaf-UYigF5iDWFE3baE7jd7g&oe=643651EF";
//    const char* filename = "file3.jpg";
//    const int num_threads = 3;
//    curl = curl_easy_init();
//
//    if (curl) {
//        if (fopen_s(&fp, filename, "wb") == 0)
//        {
//            double content_length;
//            curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
//            curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &content_length);
//            curl_easy_setopt(curl, CURLOPT_HEADER, 1);
//
//            curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
//            long long content_length_int = static_cast<long long>(content_length);
//            std::vector<std::pair<long long, long long>> download_ranges = get_download_ranges(content_length_int, num_threads);
//            std::vector<std::thread> threads;
//            for (int i = 0; i < num_threads; i++) {
//                Range range = {
//                    download_ranges[i].first,
//                    download_ranges[i].second
//                };
//                curl_easy_setopt(curl, CURLOPT_RANGE, "%d-%d", range.start, range.end);
//                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//            }
//            curl_easy_setopt(curl, CURLOPT_URL, url);
//            curl_easy_setopt(curl, CURLOPT_HEADER, 1);
//            curl_easy_perform(curl);
//            res = curl_easy_perform(curl);
//            cout << res << endl;
//            curl_easy_cleanup(curl);
//            fclose(fp);
//
//            if (res == CURLE_OK) {
//                cout << "File downloaded successfully." << endl;
//            }
//            else {
//                cout << "Failed to download file." << endl;
//            }
//        }
//        else {
//            cout << "Failed to create file." << endl;
//        }
//    }
//    return 0;
//}
