// example from
// https://matplotlib.org/stable/gallery/lines_bars_and_markers/fill_between_demo.html

#include <pybind11/embed.h>
#include <pybind11/stl.h>

#include <matplotlib_cpp11/matplotlib_cpp11.h>

#include <algorithm>
#include <vector>

namespace py = pybind11;
using namespace py::literals;

template <typename T> std::vector<T> arange(T start, T end, T h) {
  int N = static_cast<int>((end - start) / h);
  std::vector<T> xs(N);
  T val = start;
  for (int i = 0; i < N; ++i) {
    xs[i] = val;
    val += h;
  }
  return xs;
}

using namespace std;
namespace pyplot = matplotlib_cpp11;

int main1() {
  auto plt = pyplot::import();

  vector<double> x = arange(0.0, 2.0, 0.01);
  vector<double> y1, y2;
  transform(x.begin(), x.end(), back_inserter(y1),
            [](double t) { return sin(2 * M_PI * t); });
  transform(x.begin(), x.end(), back_inserter(y2),
            [](double t) { return 0.8 * sin(4 * M_PI * t); });
  auto [fig, axes] = plt.subplots(
      3, 1, py::dict("sharex"_a = true, "figsize"_a = py::make_tuple(6, 6)));
  auto ax1 = axes[0], ax2 = axes[1], ax3 = axes[2];
  ax1.fill_between(x, y1);
  ax1.set_title("fill between y1 and 0");

  ax2.fill_between(x, y1, 1);
  ax2.set_title("fill between y1 and 1");

  ax3.fill_between(x, y1, y2);
  ax3.set_title("fill between y1 and y2");
  ax3.set_xlabel("x");
  fig.tight_layout();
  plt.show();
  return 0;
}

int main2() {
  auto plt = pyplot::import();

  vector<double> x = {0, 1, 2, 3};
  vector<double> y1 = {0.8, 0.8, 0.2, 0.2};
  vector<double> y2 = {0, 0, 1, 1};
  auto [fig, axs] = plt.subplots(2, 1, py::dict("sharex"_a = true));
  auto ax1 = axs[0], ax2 = axs[1];

  ax1.set_title("interpolation=False");
  ax1.plot(x, y1, "o--");
  ax1.plot(x, y2, "o--");
  vector<bool> where = {true, true, false, false};
  ax1.fill_between(x, y1, y2, "where"_a = where, "color"_a = "C0",
                   "alpha"_a = 0.3);
  where = {false, false, true, true};
  ax1.fill_between(x, y1, y2, "where"_a = where, "color"_a = "C1",
                   "alpha"_a = 0.3);

  ax2.set_title("interpolation=True");
  ax2.plot(x, y1, "o--");
  ax2.plot(x, y2, "o--");
  where = {true, true, false, false};
  ax2.fill_between(x, y1, y2, "where"_a = where, "color"_a = "C0",
                   "alpha"_a = 0.3, "interpolate"_a = true);
  where = {false, false, true, true};
  ax2.fill_between(x, y1, y2, "where"_a = where, "color"_a = "C1",
                   "alpha"_a = 0.3, "interpolate"_a = true);
  fig.tight_layout();
  plt.show();
  return 0;
}

int main3() {
  auto plt = pyplot::import();
  auto [fig, ax] = plt.subplots();
  vector<double> x = arange(0.0, 4 * M_PI, 0.01);
  vector<double> y;
  transform(x.begin(), x.end(), back_inserter(y),
            [](double x) { return sin(x); });
  ax.plot(x, y, "color"_a = "black");
  double threshold = 0.75;
  ax.axhline(threshold, "color"_a = "green", "lw"_a = 2, "alpha"_a = 0.7);
  vector<bool> where;
  transform(y.begin(), y.end(), back_inserter(where),
            [&threshold](double y) { return y > threshold; });
  ax.fill_between(x, 0, 1, "where"_a = where, "color"_a = "green",
                  "alpha"_a = 0.5, "transform"_a = ax.get_xaxis_transform());
  plt.show();
  return 0;
}

int main() {
  py::initialize_interpreter();
  main1();
  main2();
  main3();
}
