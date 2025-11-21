
function init(this)
    this.inventory = New_Inventory(EMPTY, ALLITEMS + 1)
    this.GUID = Get_GUID()
end

function tick(this, delta)
    if Active_GUID(CENTER , this.GUID) then
        Draw_Players_Inventory(CENTER_LEFT)
        Draw_Custom_Inventory(CENTER_RIGHT, this.inventory)
    end
end

function onOpen(this)
    Actiate_GUID(CENTER, this.GUID)
end

function onAutoGive(count)
    return Take_From_Inventory(count, this.inventory)
end

function onAutoGet(item)
    return Add_To_Inventory(item, this.inventory)
end