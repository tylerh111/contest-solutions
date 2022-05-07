
import sys
from typing import List


class Gem():
    def __init__(self, id, type, value):
        self.id = id
        self.type = type
        self.value = value
    def __str__(self):
        return '({}.{}.{})'.format(self.id, self.type, self.value)


def solve(gems: List[Gem], gems_max: List[Gem], n: int):
    gems.sort(key=lambda gem: gem.value, reverse=True)
    gems_max.sort(key=lambda gem: gem.value, reverse=True)

    curr_max = -1
    curr_gem = None

    for pick1 in gems_max:
        print('========================================', file=sys.stderr)
        print('i pick     ', pick1, file=sys.stderr)
        pick2 = None

        crew_picks = 0
        crew_pick_type = None
        crew_pick_type_same = True
        for gem in gems:
            # crew skip if gem == pick1
            # crew skip if gem_type n times in a row
            if gem.id == pick1.id:
                print('skipping[1]', gem, file=sys.stderr)
                continue
            if crew_picks == 0:
                crew_pick_type = gem.type
            else:
                crew_pick_type_same = crew_pick_type_same and crew_pick_type == gem.type

            if crew_picks == n and crew_pick_type_same:
                if pick1.type != gem.type:
                    pick2 = gem
                    break
                else:
                    print('skipping[2]', gem, file=sys.stderr)
                    continue

            # i skip if gem_type == pick1_type
            crew_picks += 1
            if crew_picks <= n*2:
                print('crew pick  ', gem, crew_picks, file=sys.stderr)
            else:
                if pick2 is not None:
                    break
                elif pick2 is None and pick1.type != gem.type:
                    pick2 = gem
                    break
                else:
                    print('skipping[3]', gem, file=sys.stderr)
                    continue
            
        if pick2 is None:
            print('nothing left....')
            break

        print('i pick     ', pick2, file=sys.stderr)
        total = pick1.value + pick2.value
        if total >= curr_max:
            curr_max = total
            curr_gem = pick1
            print('!!! NEW BEST !!!', curr_max, pick1, pick2, file=sys.stderr)
        else:
            break

    return curr_gem



if __name__ == '__main__':
    m = -1

    while True:
        line = input().split()
        m = int(line[0])
        n = int(line[1])

        if m == 0: break

        gems = []
        gems_max = []

        gem_id = 0

        for i in range(m):
            line = input().split()
            code = line[0]
            vals = [int(x) for x in line[1:]]

            gems_max.append(Gem(gem_id, code, vals[0]))
            for val in vals:
                gems.append(Gem(gem_id, code, val))
                gem_id += 1

        gem = solve(gems, gems_max, n)
        print(gem.type)
        print('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~', file=sys.stderr)


