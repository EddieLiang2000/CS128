#include "illini_book.hpp"

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream people{people_fpath};
    for (std::string line; std::getline(people, line); line = "") {
        uins_.push_back(std::stoi(line));
        // FILL UP UINS!!!!!!!
    }
    std::ifstream relations{relations_fpath};
    for (std::string line; std::getline(relations, line); line = "") {
        std::vector<std::string> rows = utilities::Split(line,',');
        int uin1 = std::stoi(rows[0]);
        int uin2 = std::stoi(rows[1]);
        std::string connection = rows[2];
        adj_list_[uin1].push_back({uin2,connection});
        adj_list_[uin2].push_back({uin1,connection});
        // Assign UINS with corresponding adjacency list!!!!!
    }
    for (unsigned int i = 0; i < uins_.size(); i++) {
        if(adj_list_.count(uins_[i]) == 0) {
            adj_list_[uins_[i]].push_back({-1,"-1"});
        }   
    }
}

// int IlliniBook::GetIndex(const int& uin) const{
//     return uins_index_.at(uin);
// }

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> output;
    std::map<int,int> result = BFSGetSteps(uin,n);
    for (const auto& each : result){
        if (each.second == n) {
            output.push_back(each.first);
        }
    }
    return output;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    std::map<int,int> result = BFS(uin_1);
    return static_cast<bool>(result.count(uin_2));
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::map<int,int> result = BFS(uin_1, relationship);
    return static_cast<bool>(result.count(uin_2));
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    std::map<int,int> result = BFS(uin_1);
    return (result.count(uin_2) != 0) ? result[uin_2] : -1;
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::map<int,int> result = BFS(uin_1,relationship);
    return (result.count(uin_2) != 0) ? result[uin_2] : -1;
}

size_t IlliniBook::CountGroups() const {
    std::map<int,int> visited;
    size_t component = 0;
    for (unsigned int i = 0; i < uins_.size(); i++) {
        if (visited.count(uins_.at(i)) == 0) {
            std::map<int,int> iter = BFS(uins_.at(i));
            for (auto it = iter.cbegin(); it != iter.cend(); ++it) {
                visited[(*it).first] = 1;
            }
            // std::cout << component << std::endl;
            component++;
        }
    }
    return component;
}

std::map<int,int> IlliniBook::BFS(const int& uin) const{
    std::map<int, int> visited;
    std::queue<int> traversal;
    traversal.push(uin);
    visited[uin] = 0;
    while(!traversal.empty()) { 
        int vertex = traversal.front();
        traversal.pop();
        for (unsigned int i = 0; i < adj_list_.at(vertex).size(); i++) {
            if (visited.count(adj_list_.at(vertex).at(i).first) == 0 && adj_list_.at(vertex).at(i).first != -1) {
                traversal.push(adj_list_.at(vertex).at(i).first);
                visited[adj_list_.at(vertex).at(i).first] = visited[vertex] + 1;
            }
        }
    }
    return visited;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int,int> visited;
    size_t component = 0;
    for (unsigned int i = 0; i < uins_.size(); i++) {
        if (visited.count(uins_.at(i)) == 0) {
            std::map<int,int> iter = BFS(uins_.at(i), relationship);
            for (auto it = iter.cbegin(); it != iter.cend(); ++it) {
                visited[(*it).first] = 1;
            }
            component++;
        }
    }
    return component;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int,int> visited;
    std::map<std::string,int> onto;
    for (const auto& r : relationships) {
        onto[r] = 1;
    }
    size_t component = 0;
    for (unsigned int i = 0; i < uins_.size(); i++) {
        if (visited.count(uins_.at(i)) == 0) {
            std::map<int,int> iter = BFS(uins_.at(i), onto);
            for (auto it = iter.cbegin(); it != iter.cend(); ++it) {
                visited[(*it).first] = 1;
            }
            component++;
        }
    }
    return component;
}

std::map<int,int> IlliniBook::BFSGetSteps(const int& uin, const int& n) const{
    std::map<int, int> visited;
    std::queue<int> traversal;
    traversal.push(uin);
    visited[uin] = 0;
    while(!traversal.empty()) { 
        int vertex = traversal.front();
        if (visited[vertex] + 1 > n) {
            break;
        }
        traversal.pop();
        for (unsigned int i = 0; i < adj_list_.at(vertex).size(); i++) {
            if (visited.count(adj_list_.at(vertex).at(i).first) == 0 && adj_list_.at(vertex).at(i).first != -1) {
                traversal.push(adj_list_.at(vertex).at(i).first);
                visited[adj_list_.at(vertex).at(i).first] = visited[vertex] + 1;
            }
        }
    }
    return visited;
}

std::map<int,int> IlliniBook::BFS(const int& uin, const std::string& relation) const{
    std::map<int, int> visited;
    std::queue<int> traversal;
    traversal.push(uin);
    visited[uin] = 0;
    while(!traversal.empty()) { 
        int vertex = traversal.front();
        
        traversal.pop();
        for (unsigned int i = 0; i < adj_list_.at(vertex).size(); i++) {
            if (visited.count(adj_list_.at(vertex).at(i).first) == 0 && adj_list_.at(vertex).at(i).second == relation) {
                traversal.push(adj_list_.at(vertex).at(i).first);
                visited[adj_list_.at(vertex).at(i).first] = visited[vertex] + 1;
            }
        }
    }
    return visited;
}

std::map<int,int> IlliniBook::BFS(const int& uin, const std::map<std::string, int>& relation) const{
    std::map<int, int> visited;
    std::queue<int> traversal;
    traversal.push(uin);
    visited[uin] = 0;
    while(!traversal.empty()) { 
        int vertex = traversal.front();
        traversal.pop();
        for (unsigned int i = 0; i < adj_list_.at(vertex).size(); i++) {
            if (visited.count(adj_list_.at(vertex).at(i).first) == 0 && relation.count(adj_list_.at(vertex).at(i).second)!=0) {
                traversal.push(adj_list_.at(vertex).at(i).first);
                visited[adj_list_.at(vertex).at(i).first] = visited[vertex] + 1;
            }
        }
    }
    return visited;
}

// std::vector<int> IlliniBook::GetAdjacencyList(const int& uin) const{
//     int index = GetIndex(uin);
//     std::vector<int> output;
//     for (unsigned int i = 0; i < adj_matrix_.at(index).size(); i++) {
//         if (adj_matrix_.at(index).at(i) != "-1") {
//             output.push_back(uins_.at(i));
//         }
//     }
//     return output;
// }

// std::vector<int> IlliniBook::GetAdjacencyList(const int& uin, const std::string& relation) const {
//     int index = GetIndex(uin);
//     std::vector<int> output;
//     for (unsigned int i = 0; i < adj_matrix_.at(index).size(); i++) {
//         if (adj_matrix_.at(index).at(i) == relation) {
//             output.push_back(uins_.at(i));
//         }
//     }
//     return output;
// }

// std::vector<int> IlliniBook::GetAdjacencyList(const int& uin, const std::vector<std::string>& relation) const {
//     std::map<std::string,int> map;
//     for (const auto& r : relation) {
//         map[r] = 1;
//     }
//     int index = GetIndex(uin);
//     std::vector<int> output;
//     for (unsigned int i = 0; i < adj_matrix_.at(index).size(); i++) {
//         if (map.count(adj_matrix_.at(index).at(i)) != 0) {
//             output.push_back(uins_.at(i));
//         }
//     }
//     return output;
// }

// std::ostream& operator<<(std::ostream& os, std::vector<std::vector<std::string>> & adj_matrix) {
//     for (unsigned int row = 0; row < adj_matrix.size(); row++) {
//         os << "The " << row << " row is: ";
//         for (unsigned int col = 0; col < adj_matrix[row].size(); col++) {
//             os << adj_matrix[row][col] << "|" << " ";
//         }
//         os << std::endl;
//     }
//     return os;
// }