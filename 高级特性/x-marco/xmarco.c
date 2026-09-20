typedef int (*DifficultyFunc) (void);

#define DIFFICULTIES \
    DIFFICULTY(EASY, 1) \
    DIFFICULTY(MEDIUM, 2) \
    DIFFICULTY(HARD, 3) \
    DIFFICULTY(EXPERT, 4) \

#define DIFFICULTY(name, value) \
    int difficulty_##name(void) \
    { \
        return value; \
    }
DIFFICULTIES
#undef DIFFICULTY

#define DIFFICULTY(name, value) difficulty_##name,
static const DifficultyFunc difficulty_funcs[] = {
    DIFFICULTIES
};
#undef DIFFICULTY

/*
 * `#` 与 `##` 的区别（均作用于宏参数 name）
 *
 *   #name  → 将参数转为字符串字面量，如 #EASY → "EASY"
 *   ##name → 将参数与前一个记号拼接，如 difficulty_##EASY → difficulty_EASY
 */

/* `#` 字符串化：生成难度名称字符串数组 */
#define DIFFICULTY(name, value) #name,
static const char *difficulty_names[] = {
    DIFFICULTIES  /* 展开为 "EASY", "MEDIUM", "HARD", "EXPERT", */
};
#undef DIFFICULTY

/* `##` 记号拼接：生成难度函数指针数组（已在上方演示，此处为对照） */
#define DIFFICULTY(name, value) difficulty_##name,
static const DifficultyFunc difficulty_funcs_2[] = {
    DIFFICULTIES  /* 展开为 difficulty_EASY, difficulty_MEDIUM, difficulty_HARD, difficulty_EXPERT, */
};
#undef DIFFICULTY