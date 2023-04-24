#include <bits/stdc++.h>

#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

    bool exists_in(K const& k, std::map<K,V>& m){
        return std::find_if(m_map.begin(),m_map.end(),[&] (auto& s) { return (!(s.first < k) && !(k < s.first)); } ) != m_map.end();
    }

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(!(keyBegin < keyEnd)){
            return;
        }
        //auto pp = &m_map;
        if(m_map.size() == 0){
            m_map.insert_or_assign(keyEnd, m_valBegin);
        }
        auto it = m_map.upper_bound(keyEnd);
        auto e = m_map.end();
        auto e_it = std::prev(it);
        if(it != m_map.end()){
            if (e_it->second != val) {
			   //e = m_map.insert_or_assign(e_it, keyEnd, it->second);
                e = m_map.insert_or_assign(e_it, keyEnd, m_valBegin);
		    }
        } else {
            if(e_it != m_map.begin()){
                m_map.insert_or_assign(keyEnd, m_valBegin);
            }
        }
        auto b_it = m_map.upper_bound(keyBegin);
        b_it--;
        auto s = m_map.end();
        if (b_it->second != val) {
            s = m_map.insert_or_assign(b_it, keyBegin, val);
        }
        auto erase_b = s != m_map.end() ? s : b_it;
        auto itt = m_map.upper_bound(keyEnd);
        auto erase_e = e != m_map.end() ? e : itt;

		if (!(erase_b->first<keyBegin) && !(keyBegin<erase_b->first) && std::prev(erase_b)->second != val) {
			erase_b++;
		} else if(erase_b->first < keyBegin){
            erase_b++;
        }
        if (erase_e != m_map.end() && erase_e->second == val && (!(erase_e->first<keyEnd) && !(keyEnd<erase_e->first))) {
            if(std::next(erase_e) != m_map.end()){
                erase_e++;
            }
        }

        bool move_end = false;
        V set_val;
        if (erase_b != m_map.end()){
           if(erase_b->first < erase_e->first) {
                if(erase_e != m_map.end()){
                    auto n_it = std::next(erase_e);
                    if(n_it->second == m_valBegin){
                       auto n_last_it = std::prev(erase_e);
                       set_val = n_last_it->second;
                       move_end = true;
                       int moo = 5;
                    }
                }
                m_map.erase(erase_b, erase_e);
                if(move_end){
                    m_map.insert_or_assign(erase_e->first, set_val);
                }
            }
        }

        //std::cout << m_map.size() << " mmap sz" << '\n';
        //for(auto kv : m_map){
        //    std::cout << "k:" << kv.first << " " << "v:" << kv.second << '\n';
        //}
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};


int main()
{
    interval_map<int,int> imap(3);
    imap.assign(2,5,20);
    imap.assign(4,3,200);
    imap.assign(12,15,200);
    imap.assign(4,10,33);
    imap.assign(7,9,44);
    imap.assign(6,13,888);
    for(int i = 2; i < 15; ++i){
        std::cout << i << ':' << imap[i] << "...";
    }

    //for(int i = 2; i < 3; ++i){
    //    std::cout << "k:"<< i << " " << "v:" << imap[i] << '\n';
    //}
    return 0;
}
