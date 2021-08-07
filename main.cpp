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

void solve()
{
	int n, h, w; cin >> n >> h >> w;
	const int sh = h, sw = w;
	std::vector<std::string> vs(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> vs[i];
	}
	const int dh[] = {1, 0, -1, 0};
	const int dw[] = {0, 1, 0, -1};
	std::vector seen(n, std::vector<bool>(n));
	const std::string dir = "DRUL";
	auto valid = [&](const int h, const int w)
	{
		return h >= 0 and h < n and w >= 0 and w < n;
	};
	auto see = [&](const int h, const int w)->void
	{
		for (int i = 0; i < 4; ++i)
		{
			int ch = h, cw = w;
			while(valid(ch, cw) and vs[ch][cw] != '#')
			{
				seen[ch][cw] = true;
				ch += dh[i];
				cw += dw[i];
			}
		}
	};
	see(h, w);
	std::vector d(n, std::vector<int>(n, inf));
	std::vector back(n, std::vector<int>(n, -1));
	using T = std::tuple<int, int, int>;
	std::priority_queue<T, std::vector<T>, std::greater<>> pq;
	std::string res;
	std::string s;
	while(true)
	{
		d.assign(n, std::vector<int>(n, inf));
		d[h][w] = 0;
		pq.emplace(0, h, w);
		while(not pq.empty())
		{
			const auto [dist, h, w] = pq.top();
			pq.pop();
			if(dist > d[h][w])
				continue;
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
		int min = inf;
		int th = -1, tw = -1;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if(not seen[i][j] and min > d[i][j])
				{
					th = i;
					tw = j;
					min = d[i][j];
				}
			}
		}
		if(th == -1)
		{
			th = sh, tw = sw;
		}
		int ch = th, cw = tw;
		while(ch != h or cw != w)
		{
			see(ch, cw);
			const int b = back[ch][cw];
			s += dir[b];
			ch -= dh[b];
			cw -= dw[b];
		}
		while(not s.empty())
		{
			res += s.back();
			s.pop_back();
		}
		if(th == sh and tw == sw)
			break;
		h = th, w = tw;
	}
	cout << res << "\n";
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