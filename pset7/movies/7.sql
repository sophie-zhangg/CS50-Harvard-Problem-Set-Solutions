SELECT title, rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010 GROUP BY title ORDER BY rating DESC;