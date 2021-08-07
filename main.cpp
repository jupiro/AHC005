#include <bits/stdc++.h>
using ll = long long;
using std::cin;
using std::cout;
using std::endl;
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const int inf = (int)1e9 + 7;
const long long INF = 1LL << 60;

uint32_t xor64(void)
{
  static uint64_t x = 88172645463325252ULL;
  x = x ^ (x << 13); x = x ^ (x >> 7);
  return x = x ^ (x << 17);
}
bool seen[70][70];
bool exeseen[70][70];
std::chrono::system_clock::time_point start, end;
void solve()
{
	start = std::chrono::system_clock::now();
	int n, h, w; cin >> n >> h >> w;
	const int sh = h, sw = w;
	std::vector<std::string> vs(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> vs[i];
	}
	std::vector<std::pair<int, int>> not_block;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(vs[i][j] != '#')
			{
				not_block.emplace_back(i, j);
			}
		}
	}
	const int dh[] = {1, 0, -1, 0};
	const int dw[] = {0, 1, 0, -1};
	// std::vector seen(n, std::vector<char>(n));
	const std::string dir = "DRUL";
	auto valid = [&](const int h, const int w)
	{
		return h >= 0 and h < n and w >= 0 and w < n;
	};
	auto see = [&](const int h, const int w)->bool
	{
		if(exeseen[h][w])
			return false;
		bool ok = false;
		for (int i = 0; i < 4; ++i)
		{
			int ch = h, cw = w;
			while(valid(ch, cw) and vs[ch][cw] != '#')
			{
				if(not seen[ch][cw])
				{
					seen[ch][cw] = true;
					ok = true;
				}
				ch += dh[i];
				cw += dw[i];
			}
		}
		exeseen[h][w] = true;
		return ok;
	};

	auto discover = [&](const int h, const int w)
	{
		if(exeseen[h][w])
			return false;
		for (int i = 0; i < 4; ++i)
		{
			int ch = h, cw = w;
			while(valid(ch, cw) and vs[ch][cw] != '#')
			{
				if(not seen[ch][cw])
					return true;
				ch += dh[i];
				cw += dw[i];
			}
		}
		return false;
	};
	see(h, w);
	std::vector d(n, std::vector<int>(n, inf));
	std::vector back(n, std::vector<int>(n, -1));
	using T = std::tuple<int, int, int>;
	std::priority_queue<T, std::vector<T>, std::greater<>> pq;
	std::string res;
	std::string s;
	std::string ans;
	std::vector<int> vt, ansvt;
	std::vector<std::tuple<int, int, int>> ds;
	const double deadline = 2900;
	int jupi_loves_kkt = 0;
	while(true)
	{
		jupi_loves_kkt += 1;
		if(jupi_loves_kkt % 32 == 0)
		{
			end = std::chrono::system_clock::now();
			const double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
			if(time > deadline)
				break;
		}
		if(not vt.empty())
		{
			int p = xor64() % (int)vt.size();
			vt.resize(p + 1);
			for (const auto &[i, j] : not_block)
			{
				seen[i][j] = exeseen[i][j] = false;
			}
			const auto sz = vt.back();
			h = sh;
			w = sw;
			res.resize(sz);
			see(h, w);
			for (const auto &c : res)
			{
				if(c == 'U')
				{
					h -= 1;
				}
				if(c == 'D')
				{
					h += 1;
				}
				if(c == 'L')
				{
					w -= 1;
				}
				if(c == 'R')
				{
					w += 1;
				}
				see(h, w);
			}
		}
		while(true)
		{
			for (const auto &[i, j] : not_block)
			{
				d[i][j] = inf;
			}
			ds.clear();
			d[h][w] = 0;
			pq.emplace(0, h, w);
			const int max_size = 6;
			while(not pq.empty())
			{
				const auto [dist, h, w] = pq.top();
				pq.pop();
				if(dist > d[h][w])
					continue;
				if(discover(h, w))
				{
					ds.emplace_back(dist, h, w);
					if(ds.size() >= max_size)
					{
						while(not pq.empty())
							pq.pop();
						break;
					}
				}
				for (int i = 0; i < 4; ++i)
				{
					const int nh = h + dh[i];
					const int nw = w + dw[i];
					if(not valid(nh, nw))
						continue;
					if(vs[nh][nw] == '#')
						continue;
					if(chmin(d[nh][nw], d[h][w] + vs[nh][nw] - '0'))
					{
						back[nh][nw] = i;
						pq.emplace(d[nh][nw], nh, nw);
					}
				}
			}
			int th = -1, tw = -1;
			if(ds.empty())
			{
				th = sh, tw = sw;
			}
			else
			{
				int idx = xor64() % (int)ds.size();
				th = std::get<1>(ds[idx]);
				tw = std::get<2>(ds[idx]);
			}
			int ch = th, cw = tw;
			while(ch != h or cw != w)
			{
				// see(ch, cw);
				const int b = back[ch][cw];
				s += dir[b];
				ch -= dh[b];
				cw -= dw[b];
			}
			while(not s.empty())
			{
				res += s.back();
				s.pop_back();
				const char c = res.back();
				
				if(c == 'U')
				{
					h -= 1;
				}
				if(c == 'D')
				{
					h += 1;
				}
				if(c == 'L')
				{
					w -= 1;
				}
				if(c == 'R')
				{
					w += 1;
				}
				if(see(h, w))
					break;
			}
			s.clear();
			if(th == sh and tw == sw)
				break;
			vt.emplace_back((int)res.size());
		}
		if(ans.empty() or ans.size() > res.size())
		{
			ans = res;
			ansvt = vt;
		}
		else
		{
			res = ans;
			vt = ansvt;
		}
	}
	cout << ans << "\n";
}
int main()
{
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  int kkt = 1; 
  // cin >> kkt;
  while(kkt--)
    solve();
  return 0;
  
}