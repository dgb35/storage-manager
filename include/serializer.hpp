#ifndef STORAGE_MANAGER_SERIALIZER_HPP
#define STORAGE_MANAGER_SERIALIZER_HPP

#include <fstream>
#include <vector>

template <typename Object>
struct Serializer
{
    void save(Object object, std::ofstream out);
    std::vector<Object> load_all(std::ifstream in);
};

template <typename Object>
void Serializer<Object>::save(Object object, std::ofstream out)
{
    if (out.is_open())
        out.write(reinterpret_cast<char*>(&object), sizeof(object));
}

template <typename Object>
std::vector<Object> Serializer<Object>::load_all(std::ifstream in)
{
    Object object;
    std::vector<Object> objects;

    in.read(reinterpret_cast<char*>(&object), sizeof(object));
    while (!in.eof())
    {
        objects.push_back(object);
        in.read(reinterpret_cast<char*>(&object), sizeof(object));
    }
    return std::move(objects);
}

#endif // STORAGE_MANAGER_SERIALIZER_HPP
