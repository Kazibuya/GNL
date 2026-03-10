# get_next_line

> Lecture ligne par ligne depuis un file descriptor.

![C](https://img.shields.io/badge/language-C-blue.svg)
![Norminette](https://img.shields.io/badge/style-Norminette-00BABC.svg)
![42](https://img.shields.io/badge/school-42-black.svg)

---

## 📋 Description

`get_next_line` est un projet du cursus **École 42** dont l'objectif est d'implémenter une fonction capable de lire et retourner une ligne à la fois depuis un file descriptor (fichier, entrée standard...).

Appelée plusieurs fois de suite, elle permet de parcourir un fichier ligne par ligne sans tout charger en mémoire.

```c
char *get_next_line(int fd);
```

- Retourne la ligne lue (incluant le `\n` si présent).
- Retourne `NULL` en fin de fichier ou en cas d'erreur.

---

## 📁 Structure du projet

```
GNL/
├── get_next_line.c            # Fonction principale (partie obligatoire)
├── get_next_line_utils.c      # Fonctions utilitaires (partie obligatoire)
├── get_next_line.h            # En-tête obligatoire
│
├── get_next_line_bonus.c      # Fonction principale (partie bonus — multi-fd)
├── get_next_line_utils_bonus.c# Fonctions utilitaires (bonus)
└── get_next_line_bonus.h      # En-tête bonus
```

---

## ⚙️ Fonctionnement

### Concept clé : la variable statique

La fonction utilise une **variable statique** pour conserver le surplus de données lu entre deux appels. À chaque appel, `read()` lit un bloc de `BUFFER_SIZE` octets, accumule les données non encore retournées, puis extrait et retourne la première ligne complète.

```
Appel 1 → lit buffer → retourne "première ligne\n"
Appel 2 → utilise le reste du buffer → retourne "deuxième ligne\n"
Appel 3 → ...
Appel N → retourne NULL (EOF)
```

### `BUFFER_SIZE`

La taille du buffer est définie à la compilation via le flag `-D BUFFER_SIZE=N`. La valeur par défaut recommandée est `42`.

---

## 🚀 Compilation & Utilisation

### Intégrer GNL dans un projet

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o programme
```

### Exemple d'utilisation

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("fichier.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Lecture depuis l'entrée standard

```c
char *line = get_next_line(0); // fd = 0 → stdin
```

---

## ⭐ Bonus — Gestion de plusieurs file descriptors simultanés

La partie bonus permet de gérer **plusieurs fd ouverts en même temps**, chacun conservant son propre état de lecture grâce à un tableau de variables statiques indexé par fd.

```c
char *get_next_line(int fd); // même prototype, gère plusieurs fd
```

```c
// Exemple bonus : lire deux fichiers en alternance
line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line3 = get_next_line(fd1);
```

Compilation avec la version bonus :

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o programme_bonus
```

---

## 📌 Contraintes du projet

- Compilé avec `gcc` et les flags : `-Wall -Wextra -Werror`
- Respect de la **Norme 42** (Norminette)
- Pas de variables globales
- Utilisation de `read()`, `malloc()` et `free()` uniquement
- Pas de `lseek()` ni de variables globales
- Pas de fuites mémoire (`valgrind` recommandé pour vérification)
- `BUFFER_SIZE` doit pouvoir être défini à la compilation

---

## ⚠️ Cas limites gérés

- Fichier vide
- Ligne sans `\n` en fin de fichier
- `BUFFER_SIZE` de 1 ou très grand
- Erreur de lecture (`read` retourne `-1`)
- `fd` invalide

---

## 👤 Auteur

**Kazibuya** — [GitHub](https://github.com/Kazibuya)
