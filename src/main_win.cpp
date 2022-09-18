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
  return build_message({"��"s, std::string(game_name), "��"s});
}

std::string build_apology(const std::string_view game_name,
                          const std::string_view company_name,
                          const std::string_view headsperson_name) {
  std::vector<std::string> messages;
  messages.reserve(12);

  auto title = build_message({"<"s, std::string(company_name), " ��ǥ�̻� "s,
                              std::string(headsperson_name), "�Դϴ�.>\n\n"});
  messages.push_back(std::move(title));

  auto greeting =
      build_message({"�ȳ��ϼ���. "s, std::string(company_name), " ��ǥ�̻� "s,
                     std::string(headsperson_name), "�Դϴ�.\n\n"s});
  messages.push_back(std::move(greeting));

  auto sorry_1 =
      build_message({quoted_game_name(game_name),
                     "�� �̹� ����ȸ�� ���� �̿��ںе��� ��Ҹ��� ���� ���\n"
                     "���� ���� �밨�ϸ� �ݼ��ϰ� �ֽ��ϴ�.\n\n"s});
  messages.push_back(std::move(sorry_1));

  auto sorry_2 =
      "�̹� ����ȸ ������ �����ߴ� ���� ���� ȸ�縦 ��ǥ�Ͽ� ����� �˼��ϴٴ� "
      "������ �帳�ϴ�.\n"
      "����ȸ �� ������ ǥ���� �̼��ߴ� ���� ���ؼ��� ����帳�ϴ�.\n\n"s;
  messages.push_back(std::move(sorry_2));

  auto thank_you =
      "�׸���, ����ȸ���� �����ֽ� ���� �ǰߵ�� ��Ҹ��� ������ �е鲲 �������� ����帳�ϴ�.\n\n"s;
  messages.push_back(std::move(thank_you));

  auto sorry_3 = build_message(
      {quoted_game_name(game_name),
       "�� ���� �̿��ںе��� ���� ������ ���� ���񽺷� �������� ���ϰ�,\n"
       "������ �����Ը� �帮�� �Ǿ����ϴ�.�ŷڸ� �帮�� ���� �� �ٽ� �ѹ� ����帳�ϴ�.\n\n"s});
  messages.push_back(std::move(sorry_3));

  auto promise_1 = build_message(
      {std::string(company_name), "�� "s, quoted_game_name(game_name),
       "�� �Ʋ��ֽô� �̿��ڵ��� ��Ҹ��� �ֿ켱���� �Ͽ�\n"
       "������ � ������ �س��� �� �ֵ��� �����ڽ��ϴ�.\n\n"s});
  messages.push_back(std::move(promise_1));

  auto promise_2 = build_message(
      {quoted_game_name(game_name),
       " ����ȸ���� �����帰 ���� �κе� �̿��ںе��� ���ġ�� ������ ������\n"
       "����� �� �ֵ��� �ڼ��ϰ� ������ ������� ��� �� ���뿡 ���� "
       "�����帮�ڽ��ϴ�.\n\n"});
  messages.push_back(std::move(promise_2));

  auto promise_3 =
      "����å���� �ϳ��� ���� ������ ������, �̿��ںе��� ��뿡 ������ �� "
      "�ֵ���\n"
      "�� �ŷڸ� �ϳ��� �׾� ���� �� �ֵ��� �ּ��� ���ϰڽ��ϴ�.\n\n"s;
  messages.push_back(std::move(promise_3));

  auto request = "�ٽ� �ѹ� ��ȸ�� �ֽñ� ��Ź�帳�ϴ�.\n\n"s;
  messages.push_back(std::move(request));

  auto from = build_message(
      {"�����մϴ�.\n", std::string(headsperson_name), " �帲.\n"});
  messages.push_back(std::move(from));

  if (game_name == "�츶������ ����Ƽ ����" && company_name == "īī��������" &&
      headsperson_name == "������") {
    messages.push_back("\n** īī��������� ���� ���� �� ��������\n");
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

  std::cout << "���� �̸��� �Է��ϼ���: ";
  std::getline(std::cin, game_name);

  std::cout << "ȸ�� �̸��� �Է��ϼ���: ";
  std::getline(std::cin, company_name);

  std::cout << "��ǥ�� �̸��� �Է��ϼ���: ";
  std::getline(std::cin, headsperson_name);

  const auto apology = build_apology(game_name, company_name, headsperson_name);
  std::cout << "\n" << apology;
  write_file("4����.txt"sv, apology);

  std::string any_key;
  std::cout << "\n���� Ű�� ��������";
  std::getline(std::cin, any_key);
  return 0;
}
