# Becol
**Be**ginner **Co**ding **L**anguage

Becol is made to be a simple and easy to understand scripting language for people who want to learn how to code. Becol tries to follow a english like syntax where you "tell" things to do things. For example, lets say that you want to move a object up in a game from Becol. You could write the following
```
tell world.obj to move up 5m
```

## Modules
In Becol everything is a module. In the above example, world.obj would be the module. Actually, world is the module but world registered the module `world.*` as itself so that the `world` module can handle when `world.obj` get told something.

There are two types of modules: Compile time modules and Runtime modules.

Compile time modules are compiled into the runtime and always avalible

Runtime modules are .so or .dll files and loaded at runtime. These so files are found in a couple of ways
- `$RUNTIME_DIR/modules`
- Environment varaible `BECOL_MODULES` (same format as PATH)
- `--load module.so`
