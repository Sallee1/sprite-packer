#include "CBlockLayout.h"
#include <algorithm>

void CBlockLayout::Rank(vector<vector<int>>& bInfo)
{
    // 矩形排版算法
    cout << "排序前" << endl;
    cout << "-------------------------------------------------" << endl;
    PrintBlocks(bInfo);
    SortByMaxside(bInfo);
    cout << "排序后" << endl;
    cout << "-------------------------------------------------" << endl;
    PrintBlocks(bInfo);
}

void CBlockLayout::Fit(int BG_W, int BG_H, vector<vector<int>> bInfo)
{
    C_BG_W = BG_W;
    C_BG_H = BG_H;
    vector<Block*> blocks;
    Node* root = CreateNode(0, 0, BG_W, BG_H);

    // 创建固定矩形块
    for (int i = 0; i < bInfo.size(); i++)
    {
        Block* loopBlock = CreateBlock(bInfo[i][0], bInfo[i][1], bInfo[i][2]);
        blocks.push_back(loopBlock);
    }

    // 将矩形块逐个添加到排版空间（树）中
    for (int j = 0; j < blocks.size(); j++)
    {
        Block* block = blocks[j];
        Node* node = nullptr;
        if (node = findNode(root, block->width, block->height))
        {
            block->fit = splitNode(node, block->width, block->height);
        }
    }

    // 将排版后的结果存储在 CAns 中
    cout << "排版后的坐标和id" << endl;
    cout << "-------------------------------------------------" << endl;
    for (int k = 0; k < blocks.size(); k++)
    {
        if (blocks[k]->fit)
        {
            vector<int> tmp = { blocks[k]->fit->x, blocks[k]->fit->y, blocks[k]->id };
            CAns.push_back(tmp);
            cout << "x:" << blocks[k]->fit->x << " "
                << "y:" << blocks[k]->fit->y << " "
                << "id:" << blocks[k]->id << endl;
        }
        else
        {
            cout << "block " << k << " don't fit in board!" << endl;
            blocks[k]->x = -1;
            blocks[k]->y = -1;
        }
    }
}

int CBlockLayout::getX(int id)
{
    for (int i = 0; i < CAns.size(); i++)
    {
        if (CAns[i][2] == id)
        {
            return CAns[i][0];
        }
    }
    return INT_MIN;    // 表示放不下该矩形
}

int CBlockLayout::getY(int id)
{
    for (int i = 0; i < CAns.size(); i++)
    {
        if (CAns[i][2] == id)
        {
            return CAns[i][1];
        }
    }
    return INT_MIN;
}

//查找合适的放置Node的位置
Node* CBlockLayout::findNode(Node* root, int w, int h)
{
    if (root->used == 1)
    {

        Node* rightNode = findNode(root->right, w, h);
        Node* downNode = findNode(root->down, w, h);
        if (rightNode)
        {
            return rightNode;
        }
        if (downNode)
        {
            return downNode;
        }
    }

    else if ((w <= root->width) && (h <= root->height))
    {
        return root;
    }
    else
    {
        return nullptr;
    }
}

Node* CBlockLayout::splitNode(Node* node, int w, int h) {
    Node* down = CreateNode(node->x, node->y + h, node->width, node->height - h);

    Node* right = CreateNode(node->x + w, node->y, node->width - w, h);

    node->used = 1;
    node->width = w;
    node->height = h;
    node->right = right;
    node->down = down;

    return node;
}

void CBlockLayout::SortByMaxside(vector<vector<int>>& bInfo)
{
    auto cmpByMaxside = [](vector<int> a, vector<int> b) {return max(a[0], a[1]) > max(b[0], b[1]); };
    std::sort(bInfo.begin(), bInfo.end(), cmpByMaxside);
}
