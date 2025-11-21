import os
import json
import struct
from PIL import Image
import math
import shutil

MODS_DIR = "mods/mods"       # folder z modami
BUILD_DIR = "mods/build"     # folder wyjściowy

os.makedirs(BUILD_DIR, exist_ok=True)
os.makedirs(os.path.join(BUILD_DIR,"buildings"), exist_ok=True)


def Get_Data_json(mod_path):
    data_file = os.path.join(mod_path, "data.json")
    if not os.path.exists(data_file):
        return {"items": [], "buildings": []}
    with open(data_file, "r", encoding="utf-8") as f:
        return json.load(f)

def compile_items(mods):
    all_items = []
    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("buildings", []):
            item["texture"] = os.path.join(mod, item["texture"])
            all_items.append(item)
    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("items", []):
            item["texture"] = os.path.join(mod, item["texture"])
            all_items.append(item)

    out_file = os.path.join(BUILD_DIR, "items.bin")
    with open(out_file, "wb") as f:
        for item in all_items:
            max_stack = item.get("max_stack", 0)
            if max_stack > 255:
                raise ValueError(f"stackcount: {max_stack} of {item.get("name","")} is too large for one byte")
            f.write(max_stack.to_bytes(1, byteorder="little"))

            name = item.get("name", "")
            f.write(name.encode("utf-8"))
            f.write(b"\x01")

            description = item.get("description", "")
            f.write(description.encode("utf-8"))
            f.write(b"\x01")

            f.write(b"\x00")
    print(f"Compiled {len(all_items)} items into items.bin")

def compile_buildings(mods):
    luamonolith = ""
    all_buildings = []
    for mod in mods:
        data = Get_Data_json(mod)
        for building in data.get("buildings", []):
            building["texture"] = os.path.join(mod, building["texture"])
            building["script"] = os.path.join(mod, building["script"])
            all_buildings.append(building)
    
    out_file = os.path.join(BUILD_DIR, "buildings.bin")
    #with open(out_file, "wb") as f:
    i = 0
    for b in all_buildings:
        shutil.copy(b["texture"], os.path.join(BUILD_DIR, "buildings", os.path.basename(str(i) + ".png")))
        #shutil.copy(b["script"], os.path.join(BUILD_DIR, "buildings", os.path.basename(str(i) + ".lua")))
        luaeee = ""
        with open(b["script"], "r", encoding="utf-8") as f:
            luaeee = f.read()
        lastfromspace = luaeee.rstrip().rsplit()
        splitedasembly = ""
        for word in lastfromspace:
            if word == "function":
                splitedasembly += word + " "
                splitedasembly += "B" + str(i) + "_"   
            else: 
                if word == "BUILDINGID":
                    splitedasembly += "B" + str(i) + "_"
                else:
                    splitedasembly += word + " "
        luamonolith += splitedasembly + "\n"
        i += 1
    print(luamonolith)

    with open(os.path.join(BUILD_DIR, "buildings.lua"), "w", encoding="utf-8") as f:
        f.write(luamonolith)
            
            
    print(f"Compiled {len(all_buildings)} buildings into buildings.bin")

def compile_item_textures_square(mods, output_path="build/items.png", tile_size=8):
    textures = []

    # Zbierz wszystkie tekstury itemów

    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("buildings", []):
            tex_path = os.path.join(mod, item["texture"])
            if os.path.exists(tex_path):
                textures.append(tex_path)
            else:
                print(f"Warning: texture not found {tex_path}")

    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("items", []):
            tex_path = os.path.join(mod, item["texture"])
            if os.path.exists(tex_path):
                textures.append(tex_path)
            else:
                print(f"Warning: texture not found {tex_path}")

    if not textures:
        print("No textures found for atlas.")
        return

    num_textures = len(textures)
    # obliczamy rozmiar atlasu: najmniejsza moc 2, która pomieści wszystkie tekstury w kwadracie
    atlas_tiles_per_side = math.ceil(math.sqrt(num_textures))
    atlas_size = atlas_tiles_per_side * tile_size

    atlas = Image.new("RGBA", (atlas_size, atlas_size))

    # wklej tekstury kolejno
    for idx, tex in enumerate(textures):
        img = Image.open(tex).convert("RGBA")
        img = img.resize((tile_size, tile_size), Image.NEAREST)
        x = (idx % atlas_tiles_per_side) * tile_size
        y = (idx // atlas_tiles_per_side) * tile_size
        atlas.paste(img, (x, y))

    atlas.save(output_path)
    print(f"Compiled {num_textures} textures into square atlas {atlas_size}x{atlas_size} -> {output_path}")

def add_info_of_items_count(mods):
    all_items = []
    bilbrazil = []
    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("buildings", []):
            all_items.append(item)
            bilbrazil.append(item)
    for mod in mods:
        data = Get_Data_json(mod)
        for item in data.get("items", []):
            all_items.append(item)

    out_file = os.path.join(BUILD_DIR, "stat.bin")
    with open(out_file, "wb") as f:
        itlen = len(all_items)
        if itlen > 65535:
            raise ValueError(f"itlen: {itlen} is too large for two bytes")
        f.write(itlen.to_bytes(2, byteorder="little"))

        buli = len(bilbrazil)
        if buli > 65535:
            raise ValueError(f"itlen: {buli} is too large for two bytes")
        f.write(buli.to_bytes(2, byteorder="little"))

        
            

if __name__ == "__main__":
    mods = [os.path.join(MODS_DIR, d) for d in os.listdir(MODS_DIR) if os.path.isdir(os.path.join(MODS_DIR, d))]
    print(f"Found {len(mods)} mods")
    compile_items(mods)
    compile_buildings(mods)
    compile_item_textures_square(mods, os.path.join(BUILD_DIR, "items.png"), 8)
    add_info_of_items_count(mods)
