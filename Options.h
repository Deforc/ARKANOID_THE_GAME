#ifndef ARKANOID_THE_GAME_OPTIONS_H
#define ARKANOID_THE_GAME_OPTIONS_H

constexpr float ballRadius{ 5.f }, ballSpeed{ 1.f }, ballSpeedBonus{ 2.f };
constexpr float blockX{ 60.f }, blockY{ 20.f };
constexpr float bogeyX{ 100.f }, bogeyY{ 20.f }, bogeySpeed{ 10.f }, bogeyBonus {100.f};
constexpr float bonusX{ 10.f }, bonusY{ 10.f }, bonusSpeed{ 3.f };
constexpr int windowWidth{ 1280 }, windowHeight{ 720 };
constexpr float savingBottomHeight {20.0f};
constexpr int simpleBlockAmountX {4}, simpleBlockAmountY{4};
constexpr int undestroyableBlockAmountX {3}, undestroyableBlockAmountY{4};
constexpr int tankBlockAmountX {4}, tankBlockAmountY{4};
constexpr int speedBlockAmountX {4}, speedBlockAmountY{4};
constexpr int bonusBlockAmountX {5}, bonusBlockAmountY{4};
#endif //ARKANOID_THE_GAME_OPTIONS_H
