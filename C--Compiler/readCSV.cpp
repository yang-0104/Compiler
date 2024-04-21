// #include <sstream>
// #include "compile.h"
// vector<vector<string>> form;

// // 将CSV文件内容读取并保存到二维字符串数组中
// void initForm(const string& filename) {
//     // 打开文件
//     ifstream file(filename);
//     // 检查文件是否成功打开
//     if (!file.is_open()) {
//         cerr << "Error opening file." << endl;
//         return ;
//     }
//     string line;
//     // 逐行读取文件内容
//     while (getline(file, line)) {
//         // 存储单行数据的字符串向量
//         vector<string> row;
//         stringstream lineStream(line);
//         string cell;
//         // 使用逗号分隔符分割行内容，提取每个单元格数据
//         while (getline(lineStream, cell, ',')) { // 假设逗号是分隔符
//             row.push_back(cell);                 // 将单元格数据添加到行向量中
//         }
//         form.push_back(row); // 将行向量添加到二维向量中
//     }
//     file.close();
// }