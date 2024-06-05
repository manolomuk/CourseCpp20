#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#pragma warning(disable:4455)

using std::chrono_literals::operator""s;

int main()
{
	{
		int val{ 0 };
		std::atomic_ref ref{ val }; //or std::atomic_ref<int>
		std::jthread producer{ [&ref]() {
			int cnt{ref};
			while (cnt < 10) {
				ref = cnt++;
				ref.notify_one();
				std::this_thread::sleep_for(0.1s);
			}
			ref = -1;
			ref.notify_one();
			}
		};

		std::jthread consumer{ [&ref]() {
			int cnt { ref };
			while (cnt != -1) {
				ref.wait(cnt);
				cnt = ref; //or cnt = ref.load();
				std::cout << cnt << std::endl;
			}
			}
		};

	}
}