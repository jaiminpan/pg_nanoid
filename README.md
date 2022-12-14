# pg_nanoid
[![Lang](https://img.shields.io/badge/Language-C-green.svg)]()
[![BSD](https://img.shields.io/badge/License-BSD-green.svg)]()
[![Extension](https://img.shields.io/badge/PostgreSQL_10+-Extension-green.svg)]()

pg_nanoid is a PostgreSQL extension of unique string ID generator for Postgres.


_Inspired by the following parent project: [ai/nanoid](https://github.com/ai/nanoid)_


- **Simple**. Written with only C without other dependency.
- **Safe**. It uses hardware random generator. Can be used in clusters.
- **Short IDs**. It uses a larger alphabet than UUID (A-Za-z0-9_-). So ID size was reduced from 36 to 21 symbols.



## USE & EXAMPLE

| Function                                         |
| ------------------------------------------------ |
| gen_nanoid (size integer default 21) -> TEXT     |
| gen_nanoid (size integer, alphabet TEXT) -> TEXT |

default alphabet: `_-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`



#### * General

```sh
SELECT gen_nanoid();

CREATE TABLE test (
  id char(21) DEFAULT gen_nanoid() PRIMARY KEY
);
```

```sh
test=# create extension pg_nanoid;
CREATE EXTENSION

test=# select gen_nanoid();
      gen_nanoid
-----------------------
 uNOiG7hTmvdnLiSYfFCNQ
(1 row)

test=# select gen_nanoid(6) from generate_series(1, 5);
 gen_nanoid
------------
 9ZMwxV
 xSl2yi
 JwA7lu
 yjBxcb
 QaoWHs
(5 rows)

test=# select gen_nanoid(6, 'pg_nanoid') from generate_series(1, 5);
 gen_nanoid
------------
 ngiipd
 ggi_da
 ppnpgn
 nin___
 nonaio
(5 rows)
```



## INSTALL


#### *. Downloads

```
git clone https://github.com/jaiminpan/pg_nanoid
```

#### *. Compile

```sh
cd pg_nanoid

USE_PGXS=1 make
USE_PGXS=1 make install

# if got error when doing "USE_PGXS=1 make install"
# try "sudo USE_PGXS=1 make install"
```

##### Compile Failed Q&A
Q: Postgresql is installed customized  
A: Try following cmd firstly  
 `export PATH="$PATH:/PATH-TO-YOUR-POSTGRES/bin"`



## Misc

[Postgres PL/PGSQL Function](https://github.com/viascom/nanoid-postgres)



