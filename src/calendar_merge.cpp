#include <algorithm>
#include <iostream>
#include <vector>

// Implement a function that takes a list of calendar bookings and returns the times the person is actually busy.
// Each booking has a start time and an end time, both in minutes after midnight. A booking covers [start, end),
// so it includes its start minute and ends just before its end minute.
// Merge any bookings that overlap or touch into one block. Back-to-back meetings such as 9:00–10:00 and 10:00–11:00
// become a single block, 9:00–11:00. Return the merged blocks sorted by start time.
// You can assume start < end for every booking. The input is not sorted.

struct Booking
{
  // fraction of hours since 0:00. Maximum is 24.0.
  // TODO: constructor checking max of 24.0
  float start;
  float end;
};

std::vector<Booking> calendar_merge(const std::vector<Booking>& bookings) noexcept
{
  if (bookings.size() < 2)
  {
    return bookings;
  }

  // Sort by start time
  auto sorted_bookings = bookings;
  std::sort(sorted_bookings.begin(), sorted_bookings.end(),
            [](const Booking& a, const Booking& b) { return a.start < b.start; });

  // Merge overlaps between consecutive blocks
  for (size_t booking_idx = 0; booking_idx < sorted_bookings.size() - 1; ++ booking_idx)
  {
    // Partial overlap of bookings
    if ((sorted_bookings.at(booking_idx).end > sorted_bookings.at(booking_idx + 1).start) &&
        (sorted_bookings.at(booking_idx).end < sorted_bookings.at(booking_idx + 1).end))
    {
      sorted_bookings.at(booking_idx).end = sorted_bookings.at(booking_idx + 1).end;
      sorted_bookings.erase(sorted_bookings.begin() + booking_idx + 1);
    }
    // booking_idx completely covers booking_idx
    else if ((sorted_bookings.at(booking_idx).end > sorted_bookings.at(booking_idx + 1).start) &&
             (sorted_bookings.at(booking_idx).end > sorted_bookings.at(booking_idx + 1).end))
    {
      sorted_bookings.erase(sorted_bookings.begin() + booking_idx + 1);
    }
  }

  return sorted_bookings;
}

int main() {
  Booking b1(0, 1.3);
  Booking b2(1.0, 2.0);
  Booking b3(12, 13);
  std::vector<Booking> bookings{b1, b2, b3};
  auto merged_bookings = calendar_merge(bookings);
  for (const auto& b : merged_bookings)
  {
    std::cout << b.start << "  " << b.end << std::endl;
  }
  return 0;
}
