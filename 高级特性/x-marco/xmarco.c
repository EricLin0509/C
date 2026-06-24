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