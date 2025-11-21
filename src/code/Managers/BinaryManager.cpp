#include "BinaryManager.h"

#include "../../define.h"
#include "../Items.h"

namespace BinaryManager {
    void LoadFileAsItemsBin(std::vector<uint>& stacks, std::vector<const char*>& names, std::vector<const char*>& descriptions, const char* name) {

        std::vector<byte> datg = LoadFileToVector("resources/build/stat.bin");

        items.AllItems = datg[0] | (datg[1] << 8);
        items.totalbuildings = datg[2] | (datg[3] << 8);

        std::vector<byte> data = LoadFileToVector(name);

        stacks.resize(items.AllItems);
        names.resize(items.AllItems);
        descriptions.resize(items.AllItems);

        int pos = 0;

        for (int i = 0; i < items.AllItems && pos < data.size(); i++) {
            if (pos >= data.size()) break;

            // 1. Stack count
            stacks[i] = data[pos];
            pos++;

            // 2. Name
            size_t name_start = pos;
            while (pos < data.size() && data[pos] != 0x01) pos++;
            if (pos >= data.size()) break;
            std::string nameStr(reinterpret_cast<char*>(&data[name_start]), pos - name_start);
            pos++; // skip 0x01

            // 3. Description
            size_t desc_start = pos;
            while (pos < data.size() && data[pos] != 0x01) pos++;
            if (pos >= data.size()) break;
            std::string descStr(reinterpret_cast<char*>(&data[desc_start]), pos - desc_start);
            pos++; // skip 0x01

            // 4. Skip separator 0x00 
            pos++;

            names[i] = strdup(nameStr.c_str());
            descriptions[i] = strdup(descStr.c_str());
        }
    }

    std::vector<byte> LoadFileToVector(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            std::cerr << "File don't exists: " << path << "\n";
            return {};
        }

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<byte> buffer(size);

        if (file.read(reinterpret_cast<char*>(buffer.data()), size)) {
            return buffer;
        } else {
            std::cerr << "Błąd podczas czytania pliku!" << std::endl;
            return {};
        }
    }
}

