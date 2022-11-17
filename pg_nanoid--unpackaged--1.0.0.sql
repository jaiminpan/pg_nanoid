\echo Use "CREATE EXTENSION pg_nanoid FROM unpackaged" to load this file. \quit

ALTER EXTENSION pg_nanoid ADD function gen_nanoid(integer);
ALTER EXTENSION pg_nanoid ADD function gen_nanoid(integer, text);
