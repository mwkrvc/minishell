# minishell


` The objective of this project is to create a simple shell`

#### Usage:
```diff
! readline installation reqiered as a prerequisite
```
  * make
  * ./minishell

#### Distribution of project objectives:
   * ovanessa: launch, parser
   * mwkrvc: builtin, exec:
      * implementing simple builtins like cd, env, export, etc.
      * launching executables based on PATH variable or using a relative/absolute path
      * processing pipes, input/output redirects, heredocs
      * signal handling
