import json

# Wczytanie JSON-a
with open("mod_info_bin.json", "r", encoding="utf-8") as f:
    data = json.load(f)

mods = data.get("mods", [])

with open("mod_info.bin", "wb") as f:

    totalbuildings = sum(mod.get("adds_buildings", 0) for mod in mods)
    if totalbuildings > 65536:
            raise ValueError(f"totalbuildings {totalbuildings} jest za duże dla uint16 IDK co robić usuncie kilka budynków albo zmiencie kod aby obslugiwał uint32")
    f.write(totalbuildings.to_bytes(2, byteorder="little")) # informacja o łącznej ilośći budynków w uint16

    for mod in mods:

        name = mod.get("name", "")
        f.write(name.encode("utf-8"))
        f.write(b"\x01")

        version = mod.get("version", "")
        f.write(version.encode("utf-8"))
        f.write(b"\x01")

        description = mod.get("description", "")
        f.write(description.encode("utf-8"))
        f.write(b"\x01")

        author = mod.get("author", "")
        f.write(author.encode("utf-8"))
        f.write(b"\x01")

        f.write(b"\x00")

print("Plik items.bin został zapisany!")
