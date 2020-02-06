local firstFloor = GetDungeonFloor(currentFloor)
local coords = firstFloor:GetEntrance():GetCoords()

currentRoom = firstFloor:GetEntranceIndex()
player = CreatePrefabAtPosition("Player", vec3.new(coords.y * roomSize + roomSize/2, 0.5, coords.x * roomSize + roomSize/2))
CreatePrefabAtPosition("Enemy", vec3.new(coords.y * roomSize + roomSize/2 + 3, 0.5, coords.x * roomSize + roomSize/2))

local coords = firstFloor:GetRoomFromIndex(1):GetCoords()
local spell = CreatePrefabAtPosition("FireballSpell", vec3.new(coords.y * roomSize + roomSize/2, 1.0, coords.x * roomSize + roomSize/2))