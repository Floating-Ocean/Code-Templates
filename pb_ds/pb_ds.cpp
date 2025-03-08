#include <bits/extc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

namespace pb_ds{
    //支持增删改查合并分割的优先队列
    template<typename Type, typename Comp = less<Type>>
    using pri_queue = __gnu_pbds::priority_queue<Type, Comp, __gnu_pbds::pairing_heap_tag>;
    //平衡树
    template<typename Type, typename Comp = less<Type>>
    using treap = __gnu_pbds::tree<Type, __gnu_pbds::null_type, Comp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
    //哈希表（复杂度不可信
    template<typename Key, typename Val>
    using un_map = __gnu_pbds::gp_hash_table<Key, Val>;
} using namespace pb_ds;


//一个treap的实现例子
void treapExample(){
    int q;
    cin >> q;
    treap<pair<int, int>> tr;
    for(int i=1;i<=q;i++){
        int op, x;
        cin >> op >> x;
        switch(op) {
            case 1: {
                tr.insert({x, i}); //插入
                break;
            }
            case 2: {
                tr.erase(tr.upper_bound({x, 0})); //删除
                break;
            }
            case 3: {
                cout << tr.order_of_key({x, 0}) + 1 << '\n'; //x第一次出现的下标
                break;
            }
            case 4: {
                auto it = tr.find_by_order(x - 1); //注意排名为[0, n - 1]，需要-1！
                cout << (it == tr.end() ? inf : (*it).first) << '\n'; //排名x的数
                break;
            }
            case 5: {
                auto it = tr.upper_bound({x, 0});
                if(it == tr.begin()) cout << inf << '\n';
                else cout << (*(-- it)).first << '\n'; //前驱（小于x的最大数）
                break;
            }
            default: {
                auto it = tr.upper_bound({x, inf});
                cout << (it == tr.end() ? inf : (*it).first) << '\n'; //后驱（大于x的最小数）
                break;
            }
        }
    }
}


