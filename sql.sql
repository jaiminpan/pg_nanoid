
CREATE EXTENSION IF NOT EXISTS pgcrypto;

CREATE OR REPLACE FUNCTION nanoid(size int DEFAULT 21, alphabet text DEFAULT '_-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
    RETURNS text
    AS
$$
DECLARE
    id text := '';
    idx int := 0;
    bytes bytea;
    pos int;
    mask int;
    step int;
BEGIN
    mask := (2 << cast(floor(log(length(alphabet) - 1) / log(2)) as int)) -1;
    step := cast(ceil(1.6 * mask * size / length(alphabet)) AS int);

    while true loop
        bytes := gen_random_bytes(size);

        while idx < size loop
            pos := get_byte(bytes, idx) & mask;
            if pos < length(alphabet) then
                id := id || substr(alphabet, pos, 1);
                if length(id) >= size then
                    return id;
                end if;
            end if;
            idx = idx + 1;
        end loop;


        idx := 0;
    end loop;
END
$$ LANGUAGE plpgsql stable
;

CREATE EXTENSION IF NOT EXISTS pgcrypto;

CREATE OR REPLACE FUNCTION nanoid(size int DEFAULT 21)
RETURNS text AS $$
DECLARE
  id text := '';
  idx int := 0;
  alphabet char(64) := 'ModuleSymbhasOwnPr-0123456789ABCDEFGHNRVfgctiUvz_KqYTJkLxpZXIjQW';
  bytes bytea;
  pos int;
BEGIN
bytes := gen_random_bytes(size);
mask = 63
  WHILE idx < size LOOP
    byte := get_byte(bytes, idx) & mask;
    pos := byte + 1; -- + 1 because substr starts at 1 for some reason
    id := id || substr(alphabet, pos, 1);
    idx = idx + 1;
  END LOOP;
  RETURN id;
END
$$ LANGUAGE PLPGSQL STABLE;