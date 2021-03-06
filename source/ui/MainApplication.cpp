// Sigpatch Installer
// Copyright (c) 2020 HarukoNX
// 
// This is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this.  If not, see <http://www.gnu.org/licenses/>.

#include <ui/MainApplication.hpp>

namespace ui
{
  void MainApplication::OnLoad()
  {
    this->LockHomeButton();

    this->titleRect = pu::ui::elm::Rectangle::New(0, 0, 1280, 84, pu::ui::Color::FromHex("#BA000DFF"));

    this->titleText = pu::ui::elm::TextBlock::New(24, 0, "Sigpatch Installer", 30);
    this->titleText->SetColor(pu::ui::Color::FromHex("#FFFFFFFF"));
    this->titleText->SetY((84 - this->titleText->GetTextHeight()) / 2);

    this->versionText = pu::ui::elm::TextBlock::New(
      24 + this->titleText->GetTextWidth() + 12,
      0,
      "v" + std::to_string(APP_VERSION_MAJOR) + "." + std::to_string(APP_VERSION_MINOR) + "." + std::to_string(APP_VERSION_PATCH),
      15);
    this->versionText->SetColor(pu::ui::Color::FromHex("#FFFFFFFF"));
    this->versionText->SetY(this->titleText->GetY() + this->titleText->GetTextHeight() - this->versionText->GetTextHeight() - 7);

    this->hekateLayout = HekateLayout::New();
    this->hekateLayout->Add(this->titleRect);
    this->hekateLayout->Add(this->titleText);
    this->hekateLayout->Add(this->versionText);

    this->updateLayout = UpdateLayout::New();
    this->updateLayout->SetAppPath(this->appPath);
    this->updateLayout->Add(this->titleRect);
    this->updateLayout->Add(this->titleText);
    this->updateLayout->Add(this->versionText);

    this->patchLayout = PatchLayout::New();
    this->patchLayout->Add(this->titleRect);
    this->patchLayout->Add(this->titleText);
    this->patchLayout->Add(this->versionText);

    this->LoadLayout(this->updateLayout);
  }

  void MainApplication::LockHomeButton()
  {
    if((this->appletType != AppletType_Application && this->appletType != AppletType_SystemApplication) || this->homeButtonLocked)
    {
      return;
    }

    appletBeginBlockingHomeButtonShortAndLongPressed(0);

    homeButtonLocked = true;
  }

  void MainApplication::SetAppletType(AppletType appletType)
  {
    this->appletType = appletType;
  }

  void MainApplication::SetAppPath(std::string appPath)
  {
    this->appPath = appPath;
  }

  void MainApplication::ShowHekate()
  {
    this->LoadLayout(this->hekateLayout);
  }

  void MainApplication::ShowPatch()
  {
    this->LoadLayout(this->patchLayout);
  }

  void MainApplication::UnlockHomeButton()
  {
    if((this->appletType != AppletType_Application && this->appletType != AppletType_SystemApplication) || !this->homeButtonLocked)
    {
      return;
    }

    appletEndBlockingHomeButtonShortAndLongPressed();

    homeButtonLocked = false;
  }
}
