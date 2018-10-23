#include <iostream>
#include <memory>
#include "idevicecpp/idevicecpp.h"
#include <plist/plist.h>
#include <usbmuxd.h>
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

class Node
{
public:
    Node(plist_t node)
        : m_node(node)
    {
        if (!m_node) {
            m_node = plist_new_bool(0);
        }
    }

    Node& operator= (const std::string& value)
    {
        plist_set_string_val(m_node, value.c_str());
    }

    operator plist_t() {
        return m_node;
    }

private:
    plist_t m_node;
};

class Plist
{
public:
    explicit Plist(plist_t root)
        : m_root(root)
    {}

    Node operator [](const std::string& item) const {
        plist_t child = plist_dict_get_item(m_root, item.c_str());
        if (child != nullptr) {
            return Node(plist_copy(child));
        }
        throw std::runtime_error("Key is not set: " + item);
    }

    Node operator [](const std::string& item) {
        Node node = (plist_dict_get_item(m_root, item.c_str()));
        plist_dict_set_item(m_root, item.c_str(), node);
    }

    Node at(const std::string& key) {
        auto nodeval = plist_dict_get_item(m_root, key.c_str());
        if (nodeval) {
            return Node(nodeval);
        }
        throw std::runtime_error("No such key: " + key);
    }

    plist_t operator*() {
        return m_root;
    }

    ~Plist()
    {
        plist_free(m_root);
    }

private:
    plist_t m_root;
};

int main(int, char**)
{
    try {
        usbmuxd_subscribe(NULL, NULL);
        idevice_t device = NULL;
        idevice_new(&device, NULL);
        char* udid = nullptr;
        idevice_get_udid(device, &udid);
        std::cout << udid << std::endl;
        Plist pl(plist_new_dict());
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}
