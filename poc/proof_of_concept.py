from graphsearch import Node, GraphSearch, FullLevels, SearchType
from multiprocessing import Pool
import numpy as np


ops = {"+":lambda x,y:x+y,
        "-":lambda x,y:x-y,
        "*":lambda x,y:x*y,
        "/":lambda x,y:x//y}


class State:

    nncalls = 0

    def __init__(self, nums, hist=[]):
        self.nums = nums
        self.N = len(self.nums)
        self.hist = hist
    
    def new(self, i,j, op):
        State.nncalls+=1
        nc = self.nums.copy()
        nhist = self.hist+[(nc[i], nc[j], op)]
        nc[i] = ops[op](nc[i], nc[j])
        nc[j] = 0
        return State(nc, nhist)

    def __repr__(self):
        solstr = ""
        for n1, n2, o in self.hist:
            solstr += f", {n1} {o} {n2}"
        return str(self.nums) + " : " + solstr[2:]

def process_subtree(state):
    rs = ReachableSearch(state.nums)
    rs.full_search()
    return rs

class ReachableSearch(GraphSearch):

    def __init__(self, num_set):
        super().__init__([State(num_set),])
        self.reachable = np.zeros(900)
    
    def next(self, state):
        for r in state.nums:
            if r>=100 and r<1000:
                self.reachable[r-100] = True
        next_states = []
        for i in range(state.N):
            for j in range(i+1, state.N):
                if state.nums[i]>0 and state.nums[j]>0:
                    next_states.append(state.new(i,j, "+"))
                    next_states.append(state.new(i,j, "*"))
                    if state.nums[i]>state.nums[j]:
                        next_states.append(state.new(i,j, "-"))
                    else:
                        next_states.append(state.new(j,i, "-"))
                    if state.nums[i]%state.nums[j]==0:
                        next_states.append(state.new(i,j, "/"))
                    elif state.nums[j]%state.nums[i]==0:
                        next_states.append(state.new(j,i, "/"))

        return next_states

    def mp(self, pool):
        self.iteration()
        self.subtrees = pool.map(process_subtree, self.queue)
        for st in self.subtrees:
            self.reachable += st.reachable
        self.reachable = self.reachable>0
        self.queue = []
        self.unreachable_targets = np.arange(100, 1000)[self.reachable==0]

class SolSearch(GraphSearch):

    def __init__(self, num_set, target, find_all=False):
        super().__init__([State(num_set),])
        self.target=target
        self.sols = []
        self.closest = None
        self.find_all = find_all
    
    def early_stop(self):
        return not self.find_all and len(self.sols)>0

    def next(self, state):
        s=state
        if self.target in s.nums:
            self.sols.append(s)
        if self.closest is None:
            self.closest = s
        elif abs(self.closest.nums[0]-self.target)>abs(s.nums[0]-self.target):
            self.closest = s
        
        if state.N==1:
            return []
        next_states = []
        for i in range(state.N):
            for j in range(i+1, state.N):
                if state.nums[i]>0 and state.nums[j]>0:
                    next_states.append(state.new(i,j, "+"))
                    next_states.append(state.new(i,j, "*"))
                    if state.nums[i]>state.nums[j]:
                        next_states.append(state.new(i,j, "-"))
                    else:
                        next_states.append(state.new(j,i, "-"))
                    if state.nums[i]%state.nums[j]==0:
                        next_states.append(state.new(i,j, "/"))
                    elif state.nums[j]%state.nums[i]==0:
                        next_states.append(state.new(j,i, "/"))

        return next_states

def print_sol(gs, t):
    ss = SolSearch(gs, t)
    ss.full_search()
    print(ss.sols)


pool = Pool()
rs = ReachableSearch([1,1,6,6,10,10])
rs.mp(pool)
pool.close()
print(rs.unreachable_targets)

