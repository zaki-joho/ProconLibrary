#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

/**
 * 
 * tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> tr;
 * tr.find_by_order(k) -> k-th element(iterator)
 * tr.order_of_key(k) -> k 未満の数がいくつあるか
*/
