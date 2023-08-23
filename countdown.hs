-- based on https://www.youtube.com/watch?v=CiXDS3bBBUo (Graham Hutton course)

data OpType = Add | Sub | Mul | Div

opps = [Add, Sub, Mul, Div]

instance Show OpType where
   show o =
    case o of
      Add -> "+"
      Sub -> "-"
      Mul -> "*"
      Div -> "/"

eval :: OpType -> Int -> Int -> Int
eval o x y =
  case o of
    Add -> x + y
    Sub -> x - y
    Mul -> x * y
    Div -> x `div` y

valid :: OpType -> Int -> Int -> Bool
valid o x y = 
  case o of
    Add -> True
    Sub -> x > y
    Mul -> True
    Div -> x `mod` y == 0

-- generates simplest expression (compared to those equivalent up to op equivalences)
unique :: OpType -> Int -> Int -> Bool
unique o x y =
  case o of
    Div -> y/=1
    Mul -> x/=1 && y/=1 && x<=y
    Add -> x<=y
    Sub -> True

toconsider :: OpType -> Int -> Int -> Bool
toconsider o x y = (valid o x y) && (unique o x y)

data Expr = Val Int | Op OpType Expr Expr Int

instance Show Expr where
   show (Val n)     = show n
   show (Op o l r _) = "(" ++ show l ++ show o ++ show r ++ ")"

-- retrieve value
evaluated :: Expr -> Int
evaluated e =
  case e of
    Val n -> n
    Op _ _ _ v -> v

-- (remaining available numbers, partial expression)
type PartialSol = ([Int], Expr)

-- recursively adds all layers (of a tree of expr trees, 
-- or rather forest starting from each initial number choice)
-- the expr trees are expanded from the root
-- e.g.                  o=*    (this one is build by considering p being added on the right,
--                        / \    but could also be considered on the left,
--          +            + p=4   only one will be valid)
--         / \    ->    / \
--         1 2          1  2
children :: PartialSol -> [PartialSol]
children ([], _) = []
children (ns, e) = (foldl (++) new_on_left (map children new_on_left))
                   ++ 
                   (foldl (++) new_on_right (map children new_on_right))
                   where
                       v = evaluated e
                       new_on_left  = [ (remaining, Op o (Val p) e (eval o p v)) 
                                        | (remaining, p) <- takeone ns, o <- opps, toconsider o p v ]
                       new_on_right = [ (remaining, Op o e (Val p) (eval o v p)) 
                                        | (remaining, p) <- takeone ns, o <- opps, toconsider o v p ]

takeone :: [Int] -> [([Int], Int)]
takeone [n] = [([], n)]
takeone (n:ns) = (ns, n) : [ (n:remaining, chosen) | (remaining, chosen) <- takeone ns ]

initial_expressions :: [Int] -> [PartialSol]
initial_expressions initial_set = [ (remaining, (Val chosen)) | (remaining, chosen) <- takeone initial_set ]

reachable :: [Int] -> [PartialSol]
reachable initial_set = foldl (++) [] (map children (initial_expressions initial_set))

-- (numset, target)
type Problem = ([Int], Int)

solutions :: Problem -> [Expr]
solutions (initial_set, target) = [ e | (_, e) <- reachable initial_set, evaluated e == target ]

prob = ([1,3,7,10,25,50], 765)
main = mapM_ print (solutions prob)

