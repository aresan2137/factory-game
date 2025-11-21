import json

# Wczytanie JSON-a
with open("items_bin.json", "r", encoding="utf-8") as f:
    data = json.load(f)

items = data.get("items", [])

with open("items.bin", "wb") as f:
    for item in items:
        # Zapis stackcount jako bajt
        stackcount = item.get("stackcount", 0)
        if stackcount > 255:
            raise ValueError(f"stackcount {stackcount} is too large for one byte")
        f.write(stackcount.to_bytes(1, byteorder="little"))

        # Zapis nazwy w UTF-8 zakończonej 0x00
        name = item.get("name", "")
        f.write(name.encode("utf-8"))
        f.write(b"\x00")

print("Plik items.bin został zapisany!")
