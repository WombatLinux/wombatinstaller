
#include <argp.h>
#include <cjson/cJSON.h>
#include <limits.h>

const char *argp_program_version = "Wombat Installer v0.0.1";
const char *argp_program_bug_address = "the github repo at https://github.com/wombatlinux/wombatinstaller";
static char doc[] = "The default installer program for Wombat Linux.";
static char args_doc[] = "";
static struct argp_option options[] = {
        { "userland", 'u', "PACKAGE", 0, "Set userland package [Default is sbase]"},
        { "mirror", 'm', "MIRROR", 0, "Set USPP/USPM mirror, default is repo.wombatlinux.org"},
        {"add-package", 'p', "PACKAGE", 0, "Add a specific package"},
        { 0 }
};

struct arguments {
    char *mirror;
    char *userland;
    cJSON *packages;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'u': arguments->userland = arg; break;
        case 'm': arguments->mirror = arg; break;
        case 'p': cJSON_AddItemToObject(arguments->packages, arg, cJSON_CreateString("placeholder")); break;
        case ARGP_KEY_ARG: return 0;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char *argv[])
{
    struct arguments arguments;

    arguments.packages = cJSON_CreateObject();

    printf("Welcome to the Wombat Linux Installer\n");

    printf("Parsing any and all options...\n");
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.userland == NULL) arguments.userland = "sbase";
    if (arguments.mirror == NULL) arguments.mirror = "http://repo.wombatlinux.org";

    cJSON *config_to_have = cJSON_CreateObject();

    printf("Setting packages...\n");
    cJSON_AddItemToObject(arguments.packages, "uspm", cJSON_CreateString("placeholder"));
    cJSON_AddItemToObject(arguments.packages, arguments.userland, cJSON_CreateString("placeholder"));

    printf("Setting mirror...\n");
    cJSON_AddItemToObject(config_to_have, "mirror", cJSON_CreateString(arguments.mirror));

    char *output = cJSON_Print(arguments.packages);

    printf("%s\n", output);

    output = cJSON_Print(config_to_have);

    printf("%s\n", output);
    // ...
}