//
// Created by Arthur on 02.06.2026.
//

#ifndef CITYBUILDER_SAVE_MANAGER_H
#define CITYBUILDER_SAVE_MANAGER_H

#include <filesystem>
#include "expected"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "../../../Game/include/utils/context.h"

class SaveManager {
public:
  static void Save(Context& context, const std::string& file_path);
  static std::expected<Context, std::string> TryLoad(const std::wstring& file_path);
};

#endif  // CITYBUILDER_SAVE_MANAGER_H
