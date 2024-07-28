from collections import deque

class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def BFS(root):
    if root is None:
        return

    queue = deque([root])

    while queue:
        node = queue.popleft()
        print(node.val, end='->')

        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

def preOrderDFS(root):
    if root is None:
        return
    print(root.val, end='->')
    preOrderDFS(root.left)
    preOrderDFS(root.right)

def postOrderDFS(root):
    if root is None:
        return
    postOrderDFS(root.left)
    postOrderDFS(root.right)
    print(root.val, end='->')

def inOrderDFS(root):
    if root is None:
        return
    inOrderDFS(root.left)
    print(root.val, end='->')
    inOrderDFS(root.right)

# Example usage:
root = TreeNode(4)
root.left = TreeNode(2)
root.right = TreeNode(6)
root.left.left = TreeNode(1)
root.left.right = TreeNode(3)
root.right.left = TreeNode(5)
root.right.right = TreeNode(7)

print("BFS (Level-order):", end = "")
BFS(root)
print("")
print("DFS (Pre-order):", end = "")
preOrderDFS(root)
print("")
print("DFS (In-order):", end = "")
inOrderDFS(root)
print("")
print("DFS (Post-order)", end = "")
postOrderDFS(root)


