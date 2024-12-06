class Guard:
    guard_pointers = {"<":[-1,0], ">":[1,0], "^":[0,-1], "v":[0,1]}

    def __init__(self, map):
        self.map = map
        self.map_width = len(map[0])
        self.map_height = len(map)
        self.visited_squares = set()

        if not self.configure_guard():
            print("Guard not found in map")
            return
        
        print("Guard found at position: ", self.position)
        print("Guard facing: ", self.direction)

        while self.move():
            pass
        print(f"Visited {len(self.visited_squares)} squares")
        self.pretty_print()

    def configure_guard(self):
        for y, line in enumerate(self.map):
            for pointer in self.guard_pointers:
                if pointer in line:
                    self.position = [line.index(pointer), y]
                    self.prev_position = self.position
                    self.direction = self.guard_pointers[pointer]
                    return True
        return False

    def move(self):
        print("Moving to: ", self.position)
        next_coords = [self.position[0] + self.direction[0], self.position[1] + self.direction[1]]

        if not self.is_on_board(next_coords):
            self.visited_squares.add(self.pos_to_index(self.position))
            self.visited_squares.add(self.pos_to_index(self.prev_position))
            return False
        
        if self.map[next_coords[1]][next_coords[0]] == "#":
            self.turn()
            return True
        
        self.visited_squares.add(self.pos_to_index(self.prev_position))
        self.prev_position = self.position
        self.position = next_coords
        return True
    
    def is_on_board(self, coords):
        return coords[0] >= 0 and coords[0] < self.map_width and coords[1] >= 0 and coords[1] < self.map_height

    def turn(self):
        self.direction = [-self.direction[1], self.direction[0]]

    def pos_to_index(self, pos):
        return pos[1]*self.map_width + pos[0]   

    def pretty_print(self):
        map_str = "".join(self.map)
        for i, char in enumerate(map_str):
            if i in self.visited_squares:
                print("X", end="")
                continue
            print(char, end="")
            if i % self.map_width+1 == 0:
                print()

map_file = open("data.txt", "r")
myGuard = Guard(map_file.readlines())
map_file.close()