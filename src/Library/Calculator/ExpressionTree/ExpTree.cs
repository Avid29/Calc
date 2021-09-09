// Adam Dernis © 2021

using Calculator.ExpressionTree.Nodes;
using Calculator.ExpressionTree.Nodes.Operators;
using Calculator.ExpressionTree.Nodes.Operators.UOpers;
using Calculator.ExpressionTree.Nodes.Operators.UOpers.SignNode;
using Calculator.ExpressionTree.Nodes.Values;

namespace Calculator.ExpressionTree
{
    public class ExpTree
    {
        private BranchNode _activeNode;

        public ExpNode Root { get; private set; }

        public void AddNode(ValueNode node)
        {
            if (_activeNode == null)
            {
                // If first node
                Root = node;
            }
            else
            {
                _activeNode.AddChild(node);
            }
        }

        public void AddNode(BranchNode node)
        {
            if (node is OperNode oNode)
            {
                AddNode(oNode);
            }
            else if (_activeNode == null)
            {
                Root = node;
            }
            else
            {
                _activeNode.AddChild(node);
            }
        }

        public void AddNode(OperNode node)
        {
            bool insert = !(node is UOperNode);

            if (_activeNode == null)
            {
                // This is the first Branch Node
                if (Root != null)
                {
                    // The first node is often a ValueNode
                    // That is the only time a ValueNode will be the active or root node

                    // Makes node the new active_node
                    node.AddChild(Root);
                }

                Root = node;
                _activeNode = node;
                return;
            }

            FindInsertionNode(node);

            if (node.Priority > _activeNode.Priority)
            {
                // The new node is a lower priority than any node so far
                // or a parenthesis/function was hit
                // Add new node to top
                if (_activeNode.Priority == Priority.OVERRIDE)
                {
                    InsertOperNode(node, insert);
                }
                else if (Root == _activeNode)
                {
                    // node is new root
                    node.AddChild(Root);
                    Root = node;
                }
            }
            else if (node.Priority == _activeNode.Priority && (node is NOperNode))
            {
                for (int i = 0; i < node.ChildCount; i++)
                {
                    _activeNode.AddChild(node);
                }

                return;
            }
            else
            {
                InsertOperNode(node, insert);
            }

            _activeNode = node;
        }

        public void CloseParenthesis()
        {
            while (!(_activeNode is ParenthesisOperNode) && !_activeNode.IsRoot)
            {
                _activeNode = _activeNode.Parent;
            }

            if (_activeNode is ParenthesisOperNode pNode)
            {
                pNode.IsClosed = true;
            }
            else
            {
                throw new System.Exception("No parenthesis to close in the Expression Tree");
            }
        }

        private void FindInsertionNode(ExpNode node)
        {
            while ((_activeNode.Priority != Priority.OVERRIDE) &&
                node.Priority > _activeNode.Priority &&
                !_activeNode.IsRoot)
            {
                _activeNode = _activeNode.Parent;
            }
        }

        private void InsertOperNode(BranchNode node, bool insert)
        {
            if (insert)
            {
                _activeNode.InsertChild(node);
            } else
            {
                _activeNode.AddChild(node);
            }
        }
    }
}
