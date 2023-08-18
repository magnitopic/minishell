# Minishell

This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

<div align="center">
  <img width="324" alt="Screen Shot 2023-08-17 at 7 36 12 PM" src="https://github.com/magnitopic/minishell/assets/21156058/c24b7b53-724a-441e-bcb0-efebabc36b1c">
</div>

# Team work

This project was done alongside `Javier Sarabia`(JaviBurn).
Check him and his work out at these links:

-  [Linkedin](https://www.linkedin.com/in/javier-sarabia-224580195)
-  [GitHub](https://github.com/javiburn)
-  [42Intra](https://profile.intra.42.fr/users/jsarabia)

# Program

## Initial installation

```bash
git clone https://github.com/magnitopic/minishell.git
cd minishell
git submodule init
git submodule update
```
## Compilation and execution

```bash
make
./minishell
```

## Execution with no env

```bash
env -i ./minishell
```

# Unsupported features

The Minishell project attempts to function very similar to Bash but some features are not required or are from the bonus part.

Unclosed quotes, or special characters that are not required like `\`(backslash), `;`(semicolon) or `!!`(bang bang).

`&&` and `||` with parenthesis for priorities as well as `*`(wildcards) ar features from the bonus part.

The only implemented builtins are `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit`
