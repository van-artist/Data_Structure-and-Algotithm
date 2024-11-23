/**
 * @file main.cpp
 * @brief 使用 ListGraph 模板库的示例程序。
 *
 * ## 问题描述
 * 编写一个程序，从文件中读取地铁线路信息，并根据用户输入的起始站和目的站，计算两站之间的最少站数的乘坐方式。
 *
 * ### 输入文件格式 (bgstations.txt)
 * 每条线路由线路号和若干个站点组成，每个站点的名称和是否需要换乘（1 表示需要，0 表示不需要）。
 * 每条线路用两行表示：
 * - 第一行是线路号和站点数。
 * - 第二行是若干个站点名称和换乘标志。
 *
 * ### 输入
 * 用户输入起始站名和目的站名。
 *
 * ### 输出
 * 输出从起始站到目的站的乘坐信息，要求乘坐站数最少。
 * 换乘信息格式如下：
 * ```
 * SSN-n1(m1)-S1-n2(m2)-...-ESN
 * ```
 * 其中：
 * - `SSN` 和 `ESN` 分别为起始站名和目的站名；
 * - `n` 为乘坐的地铁线路号；
 * - `m` 为乘坐站数。
 *
 * ### 样例输入
 * 用户输入起始站 `西土城` 和目的站 `北京西站`。
 *
 * ### 样例输出
 * ```
 * 西土城-10(1)-知春路-13(2)-西直门-4(2)-国家图书馆-9(4)-北京西站
 * ```
 */
#include "ListGraph.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

/**
 * @brief 定义站点信息结构体。
 * 包含站点名称、是否需要换乘、所属线路列表、下一站指针。
 */
struct Station
{
    std::string name;
    bool replace;
    std::vector<int> curcuitIDs;
    Station *next = nullptr;

    bool operator==(const Station &other) const
    {
        return name == other.name;
    }
};

namespace std
{
    template <>
    struct hash<Station>
    {
        std::size_t operator()(const Station &station) const
        {
            return std::hash<std::string>()(station.name);
        }
    };
}

std::ostream &operator<<(std::ostream &os, const Station &station)
{
    os << "Station(name: " << station.name << ", replace: " << station.replace << ")";
    return os;
}

int main()
{
    ListGraph<int, Station> circuitMap;
    std::vector<Station> replaceStations;
    int circuitNum;
    std::ifstream file("bgstations.txt");
    if (!file)
    {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    file >> circuitNum;

    for (int i = 0; i < circuitNum; i++)
    {
        int circuitID;
        int stationNum;

        file >> circuitID >> stationNum;

        Station prevStation;
        prevStation.name = "";
        prevStation.replace = false;
        prevStation.curcuitIDs = {};
        prevStation.next = nullptr;

        bool hasPrev = false;

        for (int j = 0; j < stationNum; j++)
        {
            Station station;
            file >> station.name >> station.replace;
            station.curcuitIDs.push_back(circuitID);

            if (station.replace)
            {
                if (std::find(replaceStations.begin(), replaceStations.end(), station) == replaceStations.end())
                {
                    replaceStations.push_back(station);
                }
            }

            if (hasPrev)
            {
                circuitMap.add_edge(prevStation, station, 1);
            }

            prevStation = station;
            hasPrev = true;
        }
    }

    Station fromStation;
    Station toStation;
    std::cin >> fromStation.name;
    std::cin >> toStation.name;

    auto min_path = circuitMap.findMinPath(fromStation, toStation);

    if (min_path.empty())
    {
        std::cout << "没有找到从 " << fromStation.name << " 到 " << toStation.name << " 的路径。" << std::endl;
        return 0;
    }

    int currentLine = min_path[0].getFrom().curcuitIDs[0];
    int stationCount = 0;
    std::cout << fromStation.name;

    for (size_t i = 0; i < min_path.size(); ++i)
    {
        const auto &edge = min_path[i];
        const Station &from = edge.getFrom();
        const Station &to = edge.getTo();

        if (std::find(from.curcuitIDs.begin(), from.curcuitIDs.end(), currentLine) == from.curcuitIDs.end())
        {
            std::cout << "-" << currentLine << "(" << stationCount << ")-" << from.name;
            currentLine = from.curcuitIDs[0];
            stationCount = 0;
        }

        ++stationCount;

        if (i == min_path.size() - 1)
        {
            std::cout << "-" << currentLine << "(" << stationCount << ")-" << to.name;
        }
    }

    std::cout << std::endl;

    file.close();
    return 0;
}
