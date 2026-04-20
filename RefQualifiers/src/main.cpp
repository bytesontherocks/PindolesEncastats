#include <concepts>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {

    class NoRestrictedObject {
      public:
        NoRestrictedObject(std::vector<std::string> input_data) : v(std::move(input_data)) {}

        const std::vector<std::string>& getData() const& { return v; }
        const std::vector<std::string>& getData() const&& = delete;

      private:
        std::vector<std::string> v;
    };

    // Compile-time interface checks for NoRestrictedObject
    template <typename T>
    concept CanCallGetDataOnConstLvalue = requires(const T& x) {
        { x.getData() } -> std::same_as<const std::vector<std::string>&>;
    };

    template <typename T>
    concept CanCallGetDataOnRvalue = requires {
        std::move(std::declval<T&&>()).getData();
    };

    static_assert(CanCallGetDataOnConstLvalue<NoRestrictedObject>);
    static_assert(!CanCallGetDataOnRvalue<NoRestrictedObject>);

    auto getSensorData() {
        std::vector<std::string> data{"0x056", "0.236", "0.89"};
        return data;
    }

}  // namespace

int main() {

    const NoRestrictedObject nro{getSensorData()};

    const auto& data = nro.getData();

    // calling getData from an rvalue is calling a deleted function so produces a compile error.
    // const auto& data_from_rvalue = NoRestrictedObject{getSensorData()}.getData();
}