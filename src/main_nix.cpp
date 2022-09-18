#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {
using namespace std::string_literals;
using namespace std::string_view_literals;
namespace stdfs = std::filesystem;

std::string build_message(const std::vector<std::string> &tokens) {
  const auto len = std::accumulate(
      tokens.cbegin(), tokens.cend(), 0,
      [](const auto acc, const auto &str) { return acc + str.length(); });
  std::string new_message;
  new_message.reserve(len);
  return std::accumulate(tokens.cbegin(), tokens.cend(), std::move(new_message),
                         [](auto &&acc, const auto &str) {
                           acc.append(str);
                           return acc;
                         });
}

std::string quoted_game_name(const std::string_view game_name) {
  return build_message({"‘"s, std::string(game_name), "’"s});
}

std::string build_apology(const std::string_view game_name,
                          const std::string_view company_name,
                          const std::string_view headsperson_name) {
  std::vector<std::string> messages;
  messages.reserve(12);

  auto title = build_message({"<"s, std::string(company_name), " 대표이사 "s,
                              std::string(headsperson_name), "입니다.>\n\n"});
  messages.push_back(std::move(title));

  auto greeting =
      build_message({"안녕하세요. "s, std::string(company_name), " 대표이사 "s,
                     std::string(headsperson_name), "입니다.\n\n"s});
  messages.push_back(std::move(greeting));

  auto sorry_1 =
      build_message({quoted_game_name(game_name),
                     "의 이번 간담회를 통해 이용자분들의 목소리를 직접 듣고\n"
                     "마음 깊이 통감하며 반성하고 있습니다.\n\n"s});
  messages.push_back(std::move(sorry_1));

  auto sorry_2 =
      "이번 간담회 내용이 미흡했던 점에 대해 회사를 대표하여 대단히 죄송하다는 "
      "말씀을 드립니다.\n"
      "간담회 중 저희의 표현이 미숙했던 점에 대해서도 사과드립니다.\n\n"s;
  messages.push_back(std::move(sorry_2));

  auto thank_you =
      "그리고, 간담회에서 보내주신 많은 의견들과 목소리를 내어준 분들께 진심으로 감사드립니다.\n\n"s;
  messages.push_back(std::move(thank_you));

  auto sorry_3 = build_message(
      {quoted_game_name(game_name),
       "를 향한 이용자분들의 깊은 애정에 좋은 서비스로 보답하지 못하고,\n"
       "오히려 불편함만 드리게 되었습니다.신뢰를 드리지 못한 점 다시 한번 사과드립니다.\n\n"s});
  messages.push_back(std::move(sorry_3));

  auto promise_1 = build_message(
      {std::string(company_name), "가 "s, quoted_game_name(game_name),
       "를 아껴주시는 이용자들의 목소리를 최우선으로 하여\n"
       "진정성 어린 소통을 해나갈 수 있도록 힘쓰겠습니다.\n\n"s});
  messages.push_back(std::move(promise_1));

  auto promise_2 = build_message(
      {quoted_game_name(game_name),
       " 간담회에서 말씀드린 개선 부분도 이용자분들의 기대치에 부합해 나가며\n"
       "이행될 수 있도록 자세하고 투명한 방법으로 경과 및 내용에 대해 "
       "말씀드리겠습니다.\n\n"});
  messages.push_back(std::move(promise_2));

  auto promise_3 =
      "개선책들을 하나씩 직접 실행해 나가며, 이용자분들의 기대에 부응할 수 "
      "있도록\n"
      "또 신뢰를 하나씩 쌓아 나갈 수 있도록 최선을 다하겠습니다.\n\n"s;
  messages.push_back(std::move(promise_3));

  auto request = "다시 한번 기회를 주시길 부탁드립니다.\n\n"s;
  messages.push_back(std::move(request));

  auto from = build_message(
      {"감사합니다.\n", std::string(headsperson_name), " 드림.\n"});
  messages.push_back(std::move(from));

  if (game_name == "우마무스메 프리티 더비" && company_name == "카카오게임즈" &&
      headsperson_name == "조계현") {
    messages.push_back("\n** 카카오게임즈는 제발 정신 좀 차리세요\n");
  }

  return build_message(messages);
}

size_t write_file(const std::string_view file_path,
                  const std::string_view content) {
  const auto path = stdfs::absolute(stdfs::path(file_path));
  std::ofstream ofstr(path);
  ofstr.write(content.data(), content.size());
  return content.size();
}
} // namespace

int main() {
  std::string game_name, company_name, headsperson_name;

  std::cout << "게임 이름을 입력하세요: ";
  std::getline(std::cin, game_name);

  std::cout << "회사 이름을 입력하세요: ";
  std::getline(std::cin, company_name);

  std::cout << "대표자 이름을 입력하세요: ";
  std::getline(std::cin, headsperson_name);

  const auto apology = build_apology(game_name, company_name, headsperson_name);
  std::cout << "\n" << apology;
  write_file("4과문.txt"sv, apology);

  std::string any_key;
  std::cout << "\n엔터 키를 누르세요";
  std::getline(std::cin, any_key);
  return 0;
}
