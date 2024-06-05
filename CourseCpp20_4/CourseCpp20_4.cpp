#include <iostream>
#include <thread>
#include <chrono>
#include <latch>
#include <barrier>

#pragma warning(disable:4455)

using std::chrono_literals::operator""s;

int main()
{
	/*std::jthread th{ []() {
		for (size_t i = 0; i < 10; i++) {
			std::cout << """" << i << ", ";
			std::this_thread::sleep_for(0.00001s);
			}
		}
	};*/

	/*std::jthread th2{ [](std::stop_token token) {
		int i{};
		while (!token.stop_requested()) {
			std::cout << i++ << ", ";
			std::this_thread::sleep_for(1s);
		}
		}
	};

	std::this_thread::sleep_for(5s);
	th2.request_stop();
	std::cout << "Completed for stop!!" << std::endl;
	*/

	/*std::jthread th{ [](std::stop_token token) {
				int i{};
				while (!token.stop_requested()) {
					std::cout << std::this_thread::get_id() << " " << i++ << '\n';
					std::this_thread::sleep_for(1s);
				}
				} };
	std::stop_callback sc{ th.get_stop_token(), []() {
			std::cout << "Stop callback" << std::endl;
			}
	};

	std::this_thread::sleep_for(7s);
	th.request_stop();
	std::cout << "Completed for stop!!" << std::endl;
	*/

	/*const int MAX{ 3 };
	std::vector<std::jthread> threads;
	std::latch l{ MAX };

	for (size_t i = 0; i < MAX; ++i) {
		threads.emplace_back([&l, i]() {
			for (size_t i = 0; i < 10; ++i) {
				std::cout << std::this_thread::get_id() << " " << i << '\n';
				std::this_thread::sleep_for(0.1s);
			}
			l.count_down();
			}
		);
	}

	std::cout << "Created threads...\n";
	//l.wait();
	std::cout << "Wait completed...\n";*/

	std::vector<std::string> messages{ "one", "two", "three", "four", "five" };
	auto completed = []() noexcept {
		static std::string output = "Completed for first time...\n";
		std::cout << output << std::endl;
		output = "Done...\n";
	};
	std::barrier sync(std::ssize(messages), completed);

	auto work = [&sync](const std::string& msg) {
		std::cout << "Working on stage one: " << msg << std::endl;
		sync.arrive_and_wait();
		std::cout << "Working on stage two: " << msg << std::endl;
		sync.arrive_and_wait();
	};

	std::vector<std::jthread> threads;

	for (size_t i = 0; i < std::size(messages); ++i) {
		threads.emplace_back(std::jthread{ work, messages[i] });
	}
	std::this_thread::sleep_for(20s);

	return 0;
}