CREATE FUNCTION gen_nanoid(size integer default 21)
RETURNS TEXT
AS 'MODULE_PATHNAME', 'pg_nanoid'
-- LANGUAGE C STRICT;
LANGUAGE C VOLATILE STRICT PARALLEL SAFE;

CREATE FUNCTION gen_nanoid(size integer, alphabet TEXT)
RETURNS TEXT
AS 'MODULE_PATHNAME', 'pg_nanoid'
-- LANGUAGE C STRICT;
LANGUAGE C VOLATILE STRICT PARALLEL SAFE;