SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id JOIN people ON people.id = stars.person_id
WHERE name IN ("Johnny Depp", "Helena Bonham Carter")
GROUP BY title
HAVING COUNT(title) = 2;