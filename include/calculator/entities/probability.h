#pragma once

#include <type_traits>
#include <utility>

namespace calculator::entities {

/**
 * @brief Concept to ensure the type is a floating-point type.
 *
 * @tparam T Type to be checked.
 */
template <typename T>
concept probability_t = std::is_floating_point_v<T>;

/**
 * @class Probability
 * @brief A structure representing a probability of event.
 *
 * @tparam EventName The type of the event name.
 * @tparam Value The type of the probability value, must satisfy the probability_t concept.
 */
template <typename EventName, probability_t Value>
class Probability final {
 public:
  /**
   * @brief Default constructor.
   */
  Probability() = default;

  /**
   * @brief Constructs a Probability instance with the given event name and value.
   *
   * @param[in] name The event name.
   * @param[in] value The probability value.
   */
  Probability(const EventName& name, const Value& value);

  /**
   * @brief Constructs a Probability instance with rvalue references.
   *
   * @param[in] name The event name (rvalue reference).
   * @param[in] value The probability value (rvalue reference).
   */
  Probability(EventName&& name, Value&& value);

  /**
   * @brief Copy constructor.
   *
   * @param[in] other The other Probability instance to copy from.
   */
  Probability(const Probability& other) = default;

  /**
   * @brief Move constructor.
   *
   * @param[in] other The other Probability instance to move from.
   */
  Probability(Probability&& other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   *
   * @param other The other Probability instance to assign from.
   * @return Reference to this instance.
   */
  constexpr Probability& operator=(const Probability& other) = default;

  /**
   * @brief Move assignment operator.
   *
   * @param other The other Probability instance to assign from.
   * @return Reference to this instance.
   */
  constexpr Probability& operator=(Probability&& other) noexcept = default;

  /**
   * @brief Gets the event name.
   *
   * @return The name of the event.
   */
  [[nodiscard]] EventName GetEventName() const noexcept { return event_name_; }

  /**
   * @brief Sets the event name.
   *
   * @param[in] new_event_name The new event name.
   */
  void SetEventName(const EventName& new_event_name) {
    EventName event_name_copy{new_event_name};
    SetEventName(std::move(new_event_name));
  }

  /**
   * @brief Sets the event name with an rvalue reference.
   *
   * @param[in] new_event_name The new event name (rvalue reference).
   */
  void SetEventName(EventName&& new_event_name) { event_name_ = std::move(new_event_name); }

  /**
   * @brief Gets the probability value.
   *
   * @return The probability value.
   */
  [[nodiscard]] Value GetValue() const noexcept { return value_; }

  /**
   * @brief Sets the probability value.
   *
   * @param[in] new_value The new probability value.
   */
  void SetValue(const Value& new_value) {
    Value value_copy{new_value};
    SetValue(std::move(value_copy));
  }

  /**
   * @brief Sets the probability value with an rvalue reference.
   *
   * @param[in] new_value The new probability value (rvalue reference).
   */
  void SetValue(Value&& new_value) { value_ = std::move(new_value); }

  /**
   * @brief Changes the probability value by adding a given value.
   *
   * @param[in] value_changing The value to add to the current probability value.
   */
  void ChangeValue(const Value& value_changing) { value_ += value_changing; }

  /**
   * @brief Swaps the contents of this instance with another instance.
   *
   * @param[in] other The other Probability instance to swap with.
   */
  constexpr void Swap(Probability& other) noexcept;

  /**
   * @brief Three-way comparison operator.
   *
   * @param other The other Probability instance to compare with.
   * @return Result of the comparison as a bool.
   */
  [[nodiscard]] bool operator<=>(const Probability& other) const = default;

 private:
  EventName event_name_;  // The name of the event.
  Value value_;           // The probability value.
};

template <typename EventName, probability_t Value>
constexpr void Probability<EventName, Value>::Swap(Probability<EventName, Value>& other) noexcept {
  std::swap(event_name_, other.event_name_);
  std::swap(value_, other.value_);
}

/**
 * @brief Creates a new Probability instance.
 *
 * @tparam EventName The type of the event name.
 * @tparam Value The type of the probability value.
 * @param[in] event_name The name of the event.
 * @param[in] value The probability value.
 * @return A new Probability instance.
 */
template <typename EventName, probability_t Value>
[[nodiscard]] Probability<EventName, Value> CreateProbability(EventName event_name, Value value) {
  Probability<EventName, Value> new_instance;
  new_instance.event_name_ = event_name;
  new_instance.value_ = value;
  return new_instance;
}

}  // namespace calculator::entities