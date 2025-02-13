#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/UI/UIElement/ImageView.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include "../../header/UI/UIElement/TextView.h"
#include "../../header/Global/Servicelocator.h"
#include"../../header/Global/Config.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
namespace UI
{
    namespace GameplayUI
    {
        using namespace UIElement;
        using namespace Global;
        using namespace Sound;
        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }
        void GameplayUIController::createButton()
        {
            restart_button = new ButtonView();
        }
        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }
        void GameplayUIController::createTexts()
        {
            time_text = new TextView();
            mine_text = new TextView();

        }
        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
            initializeMineText();

        }
        void GameplayUIController::initializeButton()
        {
            restart_button->initialize("Restart Button",
                Config::restart_button_texture_path,
                button_width, button_height,
                sf::Vector2f(restart_button_left_offset, restart_button_top_offset));

            registerButtonCallback();
        }

        void GameplayUIController::registerButtonCallback()
        {
            restart_button->registerCallbackFuntion(std::bind(&GameplayUIController::restartButtonCallback, this));
        }

        void GameplayUIController::restartButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getGameplayService()->startGame();
        }
        void GameplayUIController::initializeTexts()
        {
            initializeTimeText();
        }
        void GameplayUIController::initializeTimeText()
        {
            time_text->initialize("000", sf::Vector2f(time_text_left_offset, time_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::initializeMineText()
        {
            mine_text->initialize("000", sf::Vector2f(mine_text_left_offset, mine_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::show()
        {
            restart_button->show();
            time_text->show();
            mine_text->show();
        }
        void GameplayUIController::update()
        {
            restart_button->update();
            updateTimeText();
            updateMineText();

        }
        void GameplayUIController::render()
        {
            restart_button->render();
            time_text->render();
            std::cout << "Time Text" << std::endl;
            mine_text->render();

        }
        void GameplayUIController::updateTimeText()
        {
            int remaining_time = ServiceLocator::getInstance()->getGameplayService()->getRemainingTime();
            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << remaining_time;
            std::string string_remaining_time = stream.str();
            time_text->setText(string_remaining_time);
            time_text->update();
        }

        void GameplayUIController::updateMineText()
        {
            int mines_count = ServiceLocator::getInstance()->getGameplayService()->getMinesCount();
            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << mines_count;
            std::string string_mine_count = stream.str();
            mine_text->setText(string_mine_count);
            mine_text->update();
        }

        void GameplayUIController::destroy()
        {
            delete (restart_button);
            delete (time_text);
            delete(mine_text);

        }
    }
}